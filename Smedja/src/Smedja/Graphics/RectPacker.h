/**
 * @file    RectPacker.h
 * @brief   Packs rectangles into bin(s)
 *
 * Uses an optimized version of
 * https://blackpawn.com/texts/lightmaps/default.html.
 */

#pragma once
#include "pch.h"

#include "Smedja/Graphics/Texture.h"
#include <glm/fwd.hpp>

namespace RectPacker {

/**
 * @class Rect
 * @brief A rectangle with an x, y, width, height, and a flag for rotation
 *
 * The rotation flag is used to indicate whether the rectangle has been rotated
 * 90 degrees clockwise to better fit the bin.
 *
 * @tparam T The type of the texture index. ie int, pointer, string_view, etc
 */
template <typename T>
struct Rect {
    int x, y, w, h;
    bool rotated;
    T sprite;
    // int textureIndex = -1;

    Rect() : x(0), y(0), w(0), h(0), rotated(false) {}
    Rect(int x, int y, int w, int h, bool rotated = false)
        : x(x), y(y), w(w), h(h), rotated(rotated) {}

    int area() const { return w * h; }
    int perimeter() const { return 2 * (w + h); }
};

struct RectXYWH {
    int x, y, w, h;
    RectXYWH() = default;
    RectXYWH(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
};

/**
 * @brief Packs the given rectangles into a single bin if possible. Not meant
 *        to be called directly, use pack() instead.
 *
 * Rectangles are modified in place to include their position and rotation
 * in the bin. Rotations are 90 degrees clockwise. Requires rects to be sorted.
 *
 * @param rects         A vector of rectangles to pack
 * @param binMaxW       The maximum width of the bin
 * @param binMaxH       The maximum height of the bin
 * @param padding       The padding between rectangles
 * @param discardFactor The cutoff point for discarding empty spaces
 * @return              True if packing was successful, false otherwise
 */
template <typename T>
inline static bool pack(std::vector<Rect<T>> &rects,
                        std::vector<RectXYWH> &emptySpaces, 
                        int binMaxW, int binMaxH, 
                        int padding = 0, int discardFactor = 0) {
    emptySpaces.clear();
    emptySpaces.emplace_back(0, 0, binMaxW, binMaxH);

    for (Rect<T> &rectangle: rects) {
        std::vector<RectXYWH>::reverse_iterator it = emptySpaces.rbegin();

        // padding is removed after while loop
        rectangle.w += padding;
        rectangle.h += padding;

        while (true) {
            SD_CORE_INFO("rectangle: {}, {}, {}, {}", rectangle.x, rectangle.y,
                         rectangle.w, rectangle.h);
            if (it == emptySpaces.rend()) {
                rectangle.w -= padding;
                rectangle.h -= padding;
                return false;
            }

            RectXYWH candidate = *it;

            // if rectangle is too big for the empty space, skip to next space
            if (candidate.w < rectangle.w || candidate.h < rectangle.h) {
                it++;
                continue;
            }

            // at this point, the rectangle fits in candidate space
            rectangle.x = candidate.x;
            rectangle.y = candidate.y;

            // remove candidate space
            std::iter_swap(it, emptySpaces.rbegin());
            emptySpaces.pop_back();

            const int leftoverW = candidate.w - rectangle.w;
            const int leftoverH = candidate.h - rectangle.h;

            /*      _____________________LW__
                    |                  |    |
                    |   rectangle      |  S |
                    |__________________|____|
                    |                       |
                    |                       |
                LH  |           L           |
                    |_______________________|       */
            if (leftoverW <= leftoverH) {
                 // Check if space(s) is too small to be added
                if (leftoverH >= discardFactor) {
                    emptySpaces.emplace_back(
                                        candidate.x,
                                        candidate.y + rectangle.h,
                                        candidate.w,
                                        leftoverH);

                    if (leftoverW >= discardFactor) {
                        emptySpaces.emplace_back(
                                             candidate.x + rectangle.w,
                                             candidate.y,
                                             leftoverW,
                                             rectangle.h);
                    }
                }
                break;
            }
            /*      _________________LW______
                    |         |             |
                    |         |             |
                    |rectangle|             |
                    |         |      L      |
                    |_________|             |
                LH  |    S    |             |
                    |_________|_____________|       */
            else {
                if (leftoverW > discardFactor) {
                    emptySpaces.emplace_back(
                                        candidate.x + rectangle.w,
                                        candidate.y,
                                        leftoverW,
                                        candidate.h);

                    if (leftoverH > discardFactor) {
                        emptySpaces.emplace_back(
                                            candidate.x,
                                            candidate.y + rectangle.h,
                                            rectangle.w,
                                            leftoverH);
                    }
                }
                break;
            }
        }   // end while
        rectangle.w -= padding;
        rectangle.h -= padding;
    }   // end for loop

    return true;
}

// TODO: Add support for non-square bins
/**
 * @brief Packs the given rectangles into a single optimal bin if possible
 *
 * Rectangles are modified in place to include their position and rotation.
 * Rotations are currently never used. The bin is currently always square.
 * The bin size is determined by a binary search and tries divisible by a 
 * power of 2. This is adjustable though.
 *
 * @param rects         A vector of rectangles to pack
 * @param padding       The padding between rectangles
 * @param maxDimension  The maximum dimension of the bin
 * @param minStepSize   The minimum step size for the binary search
 * @return              Width and height of the bin if packing was successful,
 *                      {-1, -1} otherwise
 */
template <typename T>
inline std::pair<int, int> pack(std::vector<Rect<T>> &rects, int padding = 0,
                                int maxDimension = 4096, int minStepSize = 64) {
    SD_CORE_ASSERT(!rects.empty(), "RectPacker::pack: rects is empty");

    // Prepare data
    std::sort(rects.begin(), rects.end(),
              [](const Rect<T> &a, const Rect<T> &b) {
                  return a.perimeter() > b.perimeter();
              });

    int discardFactor = std::min(rects.back().w, rects.back().h);

    // Binary search for the best bin size
    int currentDimension = maxDimension;
    int returnDimension  = maxDimension;
    int stepSize         = maxDimension / 2;

    std::vector<RectXYWH> emptySpaces;
    emptySpaces.reserve(rects.size() + 1);

    while (stepSize > minStepSize) {
        if (pack(rects, emptySpaces, currentDimension, currentDimension, 
                 padding, discardFactor)) {
            returnDimension   = currentDimension;
            currentDimension -= stepSize;
        } else {
            if (currentDimension == maxDimension) {
                return {-1, -1};
            }
            currentDimension += stepSize;
        }
        stepSize /= 2;
    }

    // TODO: Optimize this. this line is needed because pack modifies rects and
    // so rects is not guaranteed to be correct after last call to pack
    pack(rects, emptySpaces, returnDimension, returnDimension, padding, 
         discardFactor);

    return {returnDimension, returnDimension};
}

} // namespace RectPacker

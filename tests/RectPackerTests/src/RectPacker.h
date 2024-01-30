/**
 * @file    RectPacker.h
 * @brief   Packs rectangles into bin(s)
 *
 * Uses an optimized version of
 * https://blackpawn.com/texts/lightmaps/default.html.
 */

#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

#include "Texture.h"

namespace RectPacker {

/**
 * @class Rect
 * @brief A rectangle with an x, y, width, height, and a flag for rotation
 *
 * The rotation flag is used to indicate whether the rectangle has been rotated
 * 90 degrees clockwise to better fit the bin.
 */
struct Rect {
    int x, y, w, h;
    bool rotated;
    int textureIndex = -1;

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
 * @brief Packs the given rectangles into a single bin if possible
 *
 * Rectangles are modified in place to include their position and rotation
 * in the bin. Rotations are 90 degrees clockwise.
 *
 * @param rects         A vector of rectangles to pack
 * @param binMaxW       The maximum width of the bin
 * @param binMaxH       The maximum height of the bin
 * @param padding       The padding between rectangles
 * @param discardFactor The cutoff point for discarding empty spaces
 * @return              True if packing was successful, false otherwise
 */

inline bool pack(std::vector<Rect> &rects, std::vector<RectXYWH> &emptySpaces, int binMaxW, int binMaxH, int padding = 0, int discardFactor = 0) {
    emptySpaces.clear();
    emptySpaces.emplace_back(0, 0, binMaxW, binMaxH);

    for (Rect &rectangle: rects) {
        std::vector<RectXYWH>::reverse_iterator it = emptySpaces.rbegin();
        rectangle.w += padding;
        rectangle.h += padding;

        while (true) {
            if (it == emptySpaces.rend()) {
                rectangle.w -= padding;
                rectangle.h -= padding;
                return false;
            }

            RectXYWH candidate = *it;

            // if rectangle is too big for empty space, skip to next empty space
            if (candidate.w < rectangle.w ||
                candidate.h < rectangle.h) {
                it++;
                continue;
            }

            // at this point, the rectangle fits in the empty space
            rectangle.x = candidate.x;
            rectangle.y = candidate.y;
            std::iter_swap(it, emptySpaces.rbegin());
            emptySpaces.pop_back();

            int leftoverW = candidate.w - rectangle.w;
            int leftoverH = candidate.h - rectangle.h;

            if (leftoverW < leftoverH) {
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

/**
 * @brief Packs the given rectangles into a single bin as optimally as possible
 *
 * Uses a binary search to find the best packing. Rectangles are modified
 * in place to include their position and rotation in the bin
 *
 * @param rects         A vector of rectangles to pack
 * @param binMaxW       The maximum width of the bin
 * @param binMaxH       The maximum height of the binary
 * @param padding       The padding between rectangles
 * @param discardFactor The cutoff point for discarding empty spaces
 * @return              True if packing was successful, false otherwise
 */
inline int binarySearchPack(std::vector<Rect> &rects, int padding = 0,
                                int maxDimension = 4096, int minStepSize = 4) {
    // Prepare data
    std::sort(rects.begin(), rects.end(),
              [](const Rect &a, const Rect &b) {
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
        if (pack(rects, emptySpaces, currentDimension, currentDimension, padding, discardFactor)) {
            returnDimension   = currentDimension;
            currentDimension -= stepSize;
        } else {
            if (currentDimension == maxDimension) {
                return -1;
            }
            currentDimension += stepSize;
        }
        stepSize /= 2;
    }
    // TODO: Optimize this. this line is needed because pack modifies rects and
    // so rects is not guaranteed to be correct after last call to pack
    pack(rects, emptySpaces, returnDimension, returnDimension, padding, discardFactor);

    return returnDimension;
}

} // namespace RectPacker

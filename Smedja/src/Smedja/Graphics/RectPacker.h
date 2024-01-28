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

namespace RectPacker {

enum class Orientation { square = 0, landscape, portrait };

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
    Orientation orientation() {
        if (w > h) {
            return Orientation::landscape;
        }
        else if (h > w) {
            return Orientation::portrait;
        }
        return Orientation::square;
    }
};

// Determines whether to use landscape or portrait
inline Orientation determineOrientation(const std::vector<Rect> &rects) {
    return Orientation::landscape;
}

// Flips rectangles that need flipping based on orientation parameter
inline void flipRects(std::vector<Rect> &rects, Orientation orientation) {
    SD_CORE_ASSERT(orientation != Orientation::square,
                   "RectPacker::flipRects: Orientation cannot be square");
    if (orientation == Orientation::landscape) {
        for (Rect &rectangle : rects) {
            if (rectangle.orientation() == Orientation::portrait) {
                std::swap(rectangle.w, rectangle.h);
                rectangle.rotated = true;
            }
        }
    }
    else {
        for (Rect &rectangle : rects) {
            if (rectangle.orientation() == Orientation::landscape) {
                std::swap(rectangle.w, rectangle.h);
                rectangle.rotated = true;
            }
        }
    }
}

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
inline bool pack(std::vector<Rect> &rects, int binMaxW, int binMaxH,
                 int padding = 0, int discardFactor = 0) {
    if (rects.empty()) return true;

    struct RectXYWH {
        int x, y, w, h;
        RectXYWH() = default;
        RectXYWH(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
    };

    std::vector<RectXYWH> emptySpaces; 
    emptySpaces.reserve(rects.size() + 1);
    emptySpaces.push_back(RectXYWH(0, 0, binMaxW, binMaxH));

    std::sort(rects.begin(), rects.end(),
              [](const Rect &a, const Rect &b) { return a.perimeter() > b.perimeter(); });

    // TODO: technically, it is more efficient to have two discard factors,
    //       one for width and one for height
    discardFactor =
        std::max(discardFactor, std::min(rects.back().w, rects.back().h));

    // Start packing
    for (Rect &rectangle: rects) {
        // Unable to pack
        // TODO: early return here if needed

        std::vector<RectXYWH>::reverse_iterator it = emptySpaces.rbegin();

        while (!emptySpaces.empty()) {
            if (it == emptySpaces.rend()) {
                // no more empty spaces to check
                return false;
            }

            RectXYWH candidate = *it;

            // if rectangle is too big for the empty space, skip to next space
            if (candidate.w < rectangle.w || candidate.h < rectangle.h) {
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

            /*      _____________________LW__
                    |                  |    |
                    |   rectangle      |  S |
                    |__________________|____|
                    |                       |
                    |                       |
                LH  |           L           |
                    |_______________________|       */
            if (leftoverW < leftoverH) {
                 // Check if space(s) is too small to be added
                if (leftoverH >= discardFactor) {
                    emptySpaces.emplace_back(
                                        candidate.x,
                                        candidate.y + rectangle.h,
                                        candidate.w,
                                        candidate.h - rectangle.h);

                    if (leftoverW >= discardFactor) {
                        emptySpaces.emplace_back(
                                             candidate.x + rectangle.w,
                                             candidate.y,
                                             candidate.w - rectangle.w,
                                             rectangle.h);
                    }
                }
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
                                        candidate.w - rectangle.w,
                                        candidate.h);

                    if (leftoverH > discardFactor) {
                        emptySpaces.emplace_back(
                                            candidate.x,
                                            candidate.y + rectangle.h,
                                            rectangle.w,
                                            candidate.h - rectangle.h);
                    }
                }
            }
        }   // end while
    }   // end for loop

    return true;
}

} // namespace RectPacker

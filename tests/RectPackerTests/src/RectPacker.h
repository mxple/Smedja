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
    assert(orientation != Orientation::square);
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
inline bool pack(std::vector<Rect> &rects, int binMaxW, int binMaxH, int padding = 0, int discardFactor = 0) {
    std::vector<RectXYWH> emptySpaces;
    emptySpaces.reserve(rects.size() + 1);
    emptySpaces.emplace_back(0, 0, binMaxW, binMaxH);

    std::sort(rects.begin(), rects.end(),
              [](Rect a, Rect b) { return a.perimeter() > b.perimeter(); });
    // TODO: technically, it is more efficient to have two discard factors,
    //       one for width and one for height
    discardFactor =
        std::max(discardFactor, std::min(rects.back().w, rects.back().h));

    for (Rect &rectangle: rects) {
        std::vector<RectXYWH>::reverse_iterator it = emptySpaces.rbegin();

        while (!emptySpaces.empty()) {
            if (it == emptySpaces.rend()) {
                // no more empty spaces to check
                return false;
            }

            RectXYWH candidate = *it;

            // if rectangle is too big for empty space, skip to next empty space
            if (candidate.w < rectangle.w + padding ||
                candidate.h < rectangle.h + padding) {
                it++;
                continue;
            }

            // at this point, the rectangle fits in the empty space
            rectangle.x = candidate.x;
            rectangle.y = candidate.y;
            std::iter_swap(it, emptySpaces.rbegin());
            emptySpaces.pop_back();

            int leftoverW = candidate.w - rectangle.w - padding;
            int leftoverH = candidate.h - rectangle.h - padding;

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
                                        candidate.y + rectangle.h + padding,
                                        candidate.w,
                                        candidate.h - rectangle.h - padding);

                    if (leftoverW >= discardFactor) {
                        emptySpaces.emplace_back(
                                             candidate.x + rectangle.w + padding,
                                             candidate.y,
                                             candidate.w - rectangle.w - padding,
                                             rectangle.h + padding);
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
                                        candidate.x + rectangle.w + padding,
                                        candidate.y,
                                        candidate.w - rectangle.w - padding,
                                        candidate.h);

                    if (leftoverH > discardFactor) {
                        emptySpaces.emplace_back(
                                            candidate.x,
                                            candidate.y + rectangle.h + padding,
                                            rectangle.w + padding,
                                            candidate.h - rectangle.h - padding);
                    }
                }
                break;
            }

        }   // end while
    }   // end for loop

    return true;
}

inline bool pack2(std::vector<Rect> &rects, int binMaxW, int binMaxH, int padding = 0, int discardFactor = 0) {
    std::vector<RectXYWH> emptySpaces;
    emptySpaces.reserve(rects.size() + 1);
    emptySpaces.emplace_back(0, 0, binMaxW, binMaxH);

    for (Rect &rectangle: rects) {
        std::vector<RectXYWH>::reverse_iterator it = emptySpaces.rbegin();

        while (!emptySpaces.empty()) {
            if (it == emptySpaces.rend()) {
                return false;
            }

            RectXYWH candidate = *it;

            // if rectangle is too big for empty space, skip to next empty space
            if (candidate.w < rectangle.w + padding ||
                candidate.h < rectangle.h + padding) {
                it++;
                continue;
            }

            // at this point, the rectangle fits in the empty space
            rectangle.x = candidate.x;
            rectangle.y = candidate.y;
            std::iter_swap(it, emptySpaces.rbegin());
            emptySpaces.pop_back();

            int leftoverW = candidate.w - rectangle.w - padding;
            int leftoverH = candidate.h - rectangle.h - padding;

            if (leftoverW <= leftoverH) {
                 // Check if space(s) is too small to be added
                if (leftoverH >= discardFactor) {
                    emptySpaces.emplace_back(
                                        candidate.x,
                                        candidate.y + rectangle.h + padding,
                                        candidate.w,
                                        candidate.h - rectangle.h - padding);

                    if (leftoverW >= discardFactor) {
                        emptySpaces.emplace_back(
                                         candidate.x + rectangle.w + padding,
                                         candidate.y,
                                         candidate.w - rectangle.w - padding,
                                         rectangle.h + padding);
                    }
                }
                break;
            }
            else {
                if (leftoverW > discardFactor) {
                    emptySpaces.emplace_back(
                                        candidate.x + rectangle.w + padding,
                                        candidate.y,
                                        candidate.w - rectangle.w - padding,
                                        candidate.h);

                    if (leftoverH > discardFactor) {
                        emptySpaces.emplace_back(
                                        candidate.x,
                                        candidate.y + rectangle.h + padding,
                                        rectangle.w + padding,
                                        candidate.h - rectangle.h - padding);
                    }
                }
                break;
            }

        }   // end while
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
inline int binarySearchPack(std::vector<Rect> &rects, int binMaxW, int binMaxH, int padding = 0, int discardFactor = 0) {
    int hi = std::max(binMaxW, binMaxH);
    int lo = 0;
    int mid = 0;

    std::sort(rects.begin(), rects.end(),
              [](Rect a, Rect b) { return a.perimeter() > b.perimeter(); });

    discardFactor = std::max(discardFactor, std::min(rects.back().w, rects.back().h));

    while (lo < hi) {
        mid = (lo + hi) / 2;
        if (pack2(rects, mid, mid, padding, discardFactor)) {
            hi = mid;
        }
        else {
            lo = mid + 1;
        }
    }
    return mid;
}

} // namespace RectPacker

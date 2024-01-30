/**
 * @file    TextureAtlas.cpp
 * @brief   TextureAtlas implementation
 */

#include "TextureAtlas.h"

namespace Smedja {

// OPTIMIZE: SIMD
/**
 * @brief Sets the subimage of this atlas to the given texture.
 *
 * @param other Texture to copy from
 * @param x     X start coordinate of the subimage
 * @param y     Y start coordinate of the subimage
 */
void TextureAtlas::subImage(const Texture &other, int x, int y) {
    SD_CORE_ASSERT(m_channels == 4, "Texture::subImage: Only RGBA8 supported");

    int copyWidth = other.width();
    int copyHeight = other.height();

    // Check if size fits, if not, squeeze as much of it as it fits and warn.
    // TODO: Check for off-by-one errors
    if (x + copyWidth > m_width || y + copyHeight > m_height) {
        SD_CORE_WARN("Texture::subImage: Subimage does not fit in texture");
        copyWidth = m_width - x;
        copyHeight = m_height - y;
    }
    
    const unsigned char *sourcePtr = other.data();
    unsigned char *destPtr = m_data + (y * m_width + x) * m_channels;

    // Check channels. Internally we use RGBA8, so if the other texture has
    // fewer channels, we need to copy it pixel by pixel.
    if (other.channels() < m_channels) {
        for (int i = 0; i < copyHeight; i++) {
            for (int j = 0; j < copyWidth; j++) {
                // TODO: Unroll this loop if necessary, or use memcpy
                for (int k = 0; k < other.channels(); k++) {
                    *destPtr = *sourcePtr;
                    destPtr++; sourcePtr++;
                }
                destPtr += m_channels - other.channels() - 1;
                *destPtr = 255; // Alpha
                destPtr++;
            }
            sourcePtr += (other.width() - copyWidth) * other.width();
            destPtr += (m_width - copyWidth) * m_channels;
        }
    }
    else if (other.channels() == m_channels) {
        // Copy data into m_data line by line
        for (int i = 0; i < other.height(); i++) {
            memcpy(destPtr, sourcePtr, copyWidth * m_channels);
            sourcePtr += other.width() * other.channels();
            destPtr += m_width * m_channels;
        }
    }
    else {
        SD_CORE_WARN("Texture::subImage: Subimage has more than 4 channels");
    }
}

} // namespace Smedja

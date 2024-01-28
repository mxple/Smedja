#include "Texture.h"
#include <iostream>
// Debug guard becuase SIMD does not compile on linux without optimizations
#ifdef DEBUG
#define STBI_NO_SIMD
#endif
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Smedja {

Texture::Texture() : m_data(nullptr), m_width(0), m_height(0), m_channels(0) {}

Texture::~Texture() {
    if (m_data) {
        stbi_image_free(m_data);
    }
}

Texture::Texture(const Texture& other) :
    m_data(other.m_data), m_width(other.m_width), m_height(other.m_height),
    m_channels(other.m_channels) {}

Texture::Texture(Texture&& other) noexcept :
    m_data(other.m_data), m_width(other.m_width), m_height(other.m_height),
    m_channels(other.m_channels) {
    other.m_data = nullptr;
}

void Texture::loadFromPath(const std::string &path, int reqChan) {
    if (m_data) {
        stbi_image_free(m_data);
    }

    m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, reqChan);
}

// Probably should never be used since if we already have the texture in memory,
// we can either use that texture or memcpy from it. Only use case of this would
// be if we wanted to change the number of channels, ie convert formats.
void Texture::loadFromData(unsigned char *data, int width, int height,
                           int channels, int reqChan) {
    if (m_data) {
        stbi_image_free(m_data);
    }

    m_data = data;
    m_width = width;
    m_height = height;
    m_channels = channels;
}

// OPTIMIZE: SIMD
// Realistically should only be used with texture atlases
void Texture::subImage(Texture &other, int x, int y) {
    assert(m_channels == 4);
    int copyWidth = other.m_width;
    int copyHeight = other.m_height;

    // Check if size fits, if not, squeeze as much of it as it fits and warn.
    // TODO: Check for off-by-one errors
    if (x + copyWidth > m_width || y + copyHeight > m_height) {
        copyWidth = m_width - x;
        copyHeight = m_height - y;
    }

    unsigned char *sourcePtr = other.m_data;
    unsigned char *destPtr = m_data + (y * m_width + x) * m_channels;

    // Check channels. Internally we use RGBA8, so if the other texture has
    // fewer channels, we need to copy it pixel by pixel.
    if (other.m_channels < m_channels) {
        for (int i = 0; i < copyHeight; i++) {
            for (int j = 0; j < copyWidth; j++) {
                // TODO: Unroll this loop if necessary, or use memcpy
                for (int k = 0; k < other.m_channels; k++) {
                    *destPtr = *sourcePtr;
                    destPtr++; sourcePtr++;
                }
                destPtr += m_channels - other.m_channels - 1;
                *destPtr = 255; // Alpha
                destPtr++;
            }
            sourcePtr += (other.m_width - copyWidth) * other.m_channels;
            destPtr += (m_width - copyWidth) * m_channels;
        }
    }
    else if (other.m_channels == m_channels) {
        // Copy data into m_data line by line
        for (int i = 0; i < other.m_height; i++) {
            memcpy(destPtr, sourcePtr, copyWidth * m_channels);
            sourcePtr += other.m_width * other.m_channels;
            destPtr += m_width * m_channels;
        }
    }
    else {
        assert(false);
    }
}

void Texture::rotate90CW() {
    std::swap(m_width, m_height);

    // Rotate the image 90 degrees clockwise
    unsigned char *original_image = m_data;
    unsigned char *rotated_image = (unsigned char *)malloc(m_width * m_height * m_channels);

    unsigned char *original_index = original_image;
    for (int x = m_width - 1; x >= 0; --x) {
        for (int y = 0; y < m_height; ++y) {
            int rotated_index = (x + y * m_width) * m_channels;

            for (int c = 0; c < m_channels; ++c) {
                rotated_image[rotated_index + c] = *original_index++;
            }
        }
    }
    stbi_image_free(m_data);
    m_data = rotated_image;
}

void Texture::drawRectangleOutline(int x, int y, int w, int h,
                                   int r, int g, int b, int a) {
    assert(m_channels == 4);
    assert(x >= 0 && x < m_width);
    assert(y >= 0 && y < m_height);
    assert(x + w >= 0 && x + w <= m_width);
    assert(y + h >= 0 && y + h <= m_height);
    w--;
    h--;

    // Draw top and bottom lines
    for (int i = 0; i <= w; i++) {
        m_data[(y * m_width + x + i) * m_channels + 0] = r;
        m_data[(y * m_width + x + i) * m_channels + 1] = g;
        m_data[(y * m_width + x + i) * m_channels + 2] = b;
        m_data[(y * m_width + x + i) * m_channels + 3] = a;

        m_data[((y + h) * m_width + x + i) * m_channels + 0] = r;
        m_data[((y + h) * m_width + x + i) * m_channels + 1] = g;
        m_data[((y + h) * m_width + x + i) * m_channels + 2] = b;
        m_data[((y + h) * m_width + x + i) * m_channels + 3] = a;
    }

    // Draw left and right lines
    for (int i = 0; i <= h; i++) {
        m_data[((y + i) * m_width + x) * m_channels + 0] = r;
        m_data[((y + i) * m_width + x) * m_channels + 1] = g;
        m_data[((y + i) * m_width + x) * m_channels + 2] = b;
        m_data[((y + i) * m_width + x) * m_channels + 3] = a;

        m_data[((y + i) * m_width + x + w) * m_channels + 0] = r;
        m_data[((y + i) * m_width + x + w) * m_channels + 1] = g;
        m_data[((y + i) * m_width + x + w) * m_channels + 2] = b;
        m_data[((y + i) * m_width + x + w) * m_channels + 3] = a;
    }
}

const unsigned char *Texture::data() const {
    return m_data;
}

int Texture::width() const {
    return m_width;
}

int Texture::height() const {
    return m_height;
}

} // namespace Smedja

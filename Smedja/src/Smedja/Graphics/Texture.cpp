#include "Texture.h"
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
void Texture::loadFromData(const unsigned char *data, int width, int height,
                           int channels, int reqChan) {
    if (m_data) {
        stbi_image_free(m_data);
    }

    m_data = stbi_load_from_memory(data, width * height * channels, &m_width,
                                   &m_height, &m_channels, reqChan);
}

// OPTIMIZE: SIMD
// Realistically should only be used with texture atlases
void Texture::subImage(Texture &other, int x, int y) {
	SD_CORE_ASSERT(m_channels == 4, "Texture::subImage: Only RGBA8 supported");

	int copyWidth = other.m_width;
	int copyHeight = other.m_height;

	// Check if size fits, if not, squeeze as much of it as it fits and warn.
	// TODO: Check for off-by-one errors
	if (x + copyWidth > m_width || y + copyHeight > m_height) {
		SD_CORE_WARN("Texture::subImage: Subimage does not fit in texture");
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
				*destPtr = 255;	// Alpha
				destPtr++;
			}
			sourcePtr += (other.m_width - copyWidth) * other.m_channels;
			destPtr += (m_width - copyWidth) * m_channels;
		}
	}
	else if (other.m_channels == m_channels) {
		// Copy data into m_data line by line
		for (int i = 0; i < other.m_height; i++) {
			memcpy(sourcePtr, destPtr, copyWidth * m_channels);
			sourcePtr += (other.m_width - copyWidth) * other.m_channels;
			destPtr += (m_width - copyWidth) * m_channels;
		}
	}
	else {
		SD_CORE_WARN("Texture::subImage: Subimage has more than 4 channels");
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

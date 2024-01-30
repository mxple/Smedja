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
    SD_CORE_TRACE("Texture destroyed");
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

    // m_data = stbi_load_from_memory(data, width * height * channels, &m_width,
    //                                &m_height, &m_channels, reqChan);
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

int Texture::channels() const {
    return m_channels;
}

} // namespace Smedja

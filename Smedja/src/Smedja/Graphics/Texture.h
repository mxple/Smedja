/**
 * @file  Texture.h
 * @brief Texture class 
 *
 * TODO: const unsigned char?
 */

#pragma once

#include "pch.h"

namespace Smedja {

/**
 * @class Texture
 * @brief Texture class that manages memory on RAM + loads textures from disk.
 *
 * Texture class manages rgba8 texture data on RAM (not vram). Textures are
 * stitched together into a texture atlas by the TextureAtlas class. The
 * TextureAtlas is then uploaded to the GPU as a single texture via GLTexture.
 */
class Texture {
public:
    Texture();
    ~Texture();
    Texture(const Texture& other);
    Texture(Texture&& other) noexcept;

    void loadFromPath(const std::string &path, int reqChan = 0);
    void loadFromData(unsigned char *data, int width, int height,
                      int channels, int reqChan = 0);

    const unsigned char *data() const;

    int width() const;
    int height() const;
    int channels() const;

protected:
    unsigned char *m_data;
    int m_width;
    int m_height;
    int m_channels;
};

} // namespace Smedja

#pragma once
// Texture class manages rgba8 texture data on RAM (not vram). Textures are
// stitched together into a texture atlas by the TextureAtlas class. The
// TextureAtlas is then uploaded to the GPU as a single texture via GLTexture.

#include <string>

namespace Smedja {

class Texture {
public:
    Texture();
    ~Texture();
    Texture(const Texture &other);
    Texture(Texture &&other) noexcept;

    void loadFromPath(const std::string &path, int reqChan = 0);
    void loadFromData(unsigned char *data, int width, int height, int channels,
                      int reqChan = 0);

    void subImage(Texture &other, int x, int y);
    void rotate90CW();
    void drawRectangleOutline(int x, int y, int w, int h, int r, int g, int b,
                              int a = 255);

    const unsigned char *data() const;

    int width() const;
    int height() const;

private:
    unsigned char *m_data;
    int m_width;
    int m_height;
    int m_channels;
};

} // namespace Smedja

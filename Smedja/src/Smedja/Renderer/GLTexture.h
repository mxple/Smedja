#pragma once

#include "pch.h"
#include <glad/glad.h>

namespace Smedja {

// Texture is wrapper for opengl texture, not rgb data
// Currently only officially suports jpg and png (3-4 color channel rgb/rgba)
class GLTexture {
public:
    GLTexture();
    GLTexture(const std::string &path, GLenum textureFormat = GL_RGB);
    ~GLTexture();

    void setData(const std::string &path, GLenum textureFormat = GL_RGB);
    void setData(const unsigned char *data, int width, int height,
                 int channels);

    void bind(unsigned int textureUnit = 0);
    void unbind();

    void setParam(GLenum name, GLenum value);

    unsigned int id() const;

private:
    unsigned int m_ID;
};

} // namespace Smedja

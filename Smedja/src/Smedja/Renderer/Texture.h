#pragma once

#include <glad/glad.h>
#include "pch.h"

namespace Smedja {

// Texture is wrapper for opengl texture, not rgb data
// Currently only officially suports jpg and png (3-4 color channel rgb/rgba)
class Texture {
public:
    Texture(const std::string& path, GLenum textureFormat = GL_RGB);
    ~Texture();

    void bind(unsigned int textureUnit = 0);
    void unbind();

    void setParam(GLenum name, GLenum value);

private:
    unsigned int m_ID;
};

} // namespace Smedja

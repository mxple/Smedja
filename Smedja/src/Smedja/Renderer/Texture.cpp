#include "Texture.h"
#ifdef DEBUG
#define STBI_NO_SIMD
#endif
#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <stb_image.h>

namespace Smedja {

// TODO support different formats and outputs
Texture::Texture(const std::string &path, GLenum textureFormat) {
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);

    // set params here if wanted

    stbi_set_flip_vertically_on_load(true);  
    int width, height, nrChannels;
    unsigned char *data =
        stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        GLenum imageFormat = nrChannels == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0,
                     imageFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        SD_CORE_WARN("Failed to load texture: {0}", path);
    }

    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_ID);
}

void Texture::bind(unsigned int textureUnit) {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setParam(GLenum name, GLenum value) {
    // pretty sure this is necessary, maybe do testing later
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexParameteri(GL_TEXTURE_2D, name, value);
}

} // namespace Smedja

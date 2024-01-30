/**
 * @file
 * @brief
 */

#include "Sprite.h"
#include <stb_image.h>

namespace Smedja {

Sprite::Sprite() = default;

Sprite::Sprite(const glm::vec2 &texCoord1, const glm::vec2 &texCoord2,
               const glm::vec2 &origin, const glm::vec2 &size)
    : m_texCoord1(texCoord1), m_texCoord2(texCoord2), m_origin(origin),
      m_size(size) {}

Sprite::Sprite(const glm::vec2 &texCoord1, const glm::vec2 &texCoord2,
               const glm::vec2 &origin, const glm::vec2 &size,
               std::shared_ptr<GLTexture> &textureAtlas)
    : m_texCoord1(texCoord1), m_texCoord2(texCoord2), m_origin(origin),
      m_size(size), m_textureAtlas(textureAtlas) {}

// Setters

void Sprite::setTexCoords(const glm::vec2 &texCoord1,
                          const glm::vec2 &texCoord2) {
    m_texCoord1 = texCoord1;
    m_texCoord2 = texCoord2;
}

void Sprite::setTexCoord1(const glm::vec2 &texCoord1) {
    m_texCoord1 = texCoord1;
}

void Sprite::setTexCoord2(const glm::vec2 &texCoord2) {
    m_texCoord2 = texCoord2;
}

void Sprite::setOrigin(const glm::vec2 &origin) {
    m_origin = origin;
}

void Sprite::setSize(const glm::vec2 &size) {
    m_size = size;
}

void Sprite::setTextureAtlas(std::shared_ptr<GLTexture> &textureAtlas) {
    m_textureAtlas = textureAtlas;
}

// Getters

const glm::vec2 &Sprite::texCoord1() const {
    return m_texCoord1;
}

const glm::vec2 &Sprite::texCoord2() const {
    return m_texCoord2;
}

const glm::vec2 &Sprite::origin() const {
    return m_origin;
}

const glm::ivec2 &Sprite::size() const {
    return m_size;
}

const std::shared_ptr<GLTexture> &Sprite::textureAtlas() const {
	return m_textureAtlas;
}

} // namespace Smedja

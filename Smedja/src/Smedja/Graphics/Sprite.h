#pragma once

#include "Smedja/Renderer/GLTexture.h"
#include "Smedja/Graphics/Texture.h"
#include "glm/glm.hpp"
#include "pch.h"

namespace Smedja {

/**
 * @class Sprite
 * @brief Sprites are responsible for managing texel coords based of a texture 
 *        atlas. It may also hold data for collision detection, but that is not
 *        yet implemented.
 *
 * Sprites are created by the ResourceManager and drawn by Renderer2D.
 * Its size should be the same as the size of the texture it is using.
 */
class Sprite {
    friend class ResourceManager;

public:
    void setTexCoords(const glm::vec2 &texCoord1, const glm::vec2 &texCoord2);
    void setTexCoord1(const glm::vec2 &texCoord1);
    void setTexCoord2(const glm::vec2 &texCoord2);
    void setOrigin(const glm::vec2 &origin);
    void setSize(const glm::vec2 &size);
    void setTextureAtlas(std::shared_ptr<GLTexture> &textureAtlas);

    const glm::vec2 &texCoord1() const;
    const glm::vec2 &texCoord2() const;
    const glm::vec2 &origin() const;
    const glm::ivec2 &size() const;
    const std::shared_ptr<GLTexture> &textureAtlas() const;

private:
    Sprite();
    Sprite(const glm::vec2 &texCoord1, const glm::vec2 &texCoord2,
           const glm::vec2 &origin, const glm::vec2 &size);
    Sprite(const glm::vec2 &texCoord1, const glm::vec2 &texCoord2,
           const glm::vec2 &origin, const glm::vec2 &size,
           std::shared_ptr<GLTexture> &textureAtlas);
    // consider deleting copy and move constructors

private:
    glm::vec2 m_texCoord1{0, 0};
    glm::vec2 m_texCoord2{1, 1};
    glm::vec2 m_origin{0, 0};
    glm::ivec2 m_size{0, 0};
    std::shared_ptr<GLTexture> m_textureAtlas;
};

} // namespace Smedja

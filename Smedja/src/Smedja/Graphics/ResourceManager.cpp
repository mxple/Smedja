/**
 * @file    ResourceManager.cpp
 * @brief   ResourceManager implementation
 */

#include "ResourceManager.h"
#include "RectPacker.h"

namespace Smedja {

// ResourceManager &ResourceManager::instance() {
//     static ResourceManager instance;
//     return instance;
// }

void ResourceManager::reload() {
    // reset atlases and pointers
    for (auto &[name, sprite] : m_sprites) {
        sprite.m_textureAtlas.reset();
    }
    // m_textureAtlases.clear();

    // prepare data for packing
    std::vector<RectPacker::Rect<std::string_view>> rects;
    for (const auto &[name, sprite] : m_sprites) {
        // skip sprites without textures
        if (m_spriteToTextureMap.find(name) == m_spriteToTextureMap.end()) {
            continue;
        }
        rects.emplace_back(0, 0, sprite.size().x, sprite.size().y);
        rects.back().sprite = name;
    }

    std::pair<int, int> dims = RectPacker::pack(rects);

    SD_CORE_ASSERT(dims.first != -1 && dims.second != -1,
                   "ResourceManager::reload: Packing failed");

    // TextureAtlas &atlas = m_textureAtlases.emplace_back();
    TextureAtlas atlas;
    unsigned char *data = (unsigned char *)calloc(dims.first * dims.second * 4,
                                                  sizeof(unsigned char));
    atlas.loadFromData(data, dims.first, dims.second, 4);

    std::shared_ptr<GLTexture> atlasGLTexture(new GLTexture());

    // Write to atlas file and update sprites
    for (const auto &rect : rects) {
        // Every sprite in rect should have a texture (see start of function)
        const Texture &texture = m_textures[m_spriteToTextureMap[rect.sprite]];
        atlas.subImage(texture, rect.x, rect.y);

        Sprite &sprite = m_sprites.find(rect.sprite)->second;
        sprite.setTexCoord1({(float)rect.x / dims.first,
                             (float)rect.y / dims.second});
        sprite.setTexCoord2({(float)(rect.x + rect.w) / dims.first,
                             (float)(rect.y + rect.h) / dims.second});
        sprite.setTextureAtlas(atlasGLTexture);
    }

    // TODO: decide whether to free data
    // atlas goes out of scope here, data is deleted (?)
}

void ResourceManager::addTexture(const std::string_view name,
                                 const std::string &path) {
    m_textures.emplace(name, Texture());
    m_textures[name].loadFromPath(path);
}

void ResourceManager::createSprite(const std::string_view name, const std::string_view texture) {
    m_sprites.emplace(name, Sprite());
    SD_CORE_ASSERT(m_textures.find(texture) != m_textures.end(),
                   "Texture {} not found!", texture);
    m_spriteToTextureMap[name] = texture;
}

void ResourceManager::createSprite(const std::string_view name) {
    m_sprites.emplace(name, Sprite());
}

void ResourceManager::setSpriteTexture(const std::string_view spriteName,
                                       const std::string_view textureName) {
    m_spriteToTextureMap[spriteName] = textureName;
}

void ResourceManager::removeSprite(const std::string_view name) {
    m_sprites.erase(name);
}

void ResourceManager::removeTexture(const std::string_view name) {
    m_textures.erase(name);
}

Sprite &ResourceManager::getSprite(const std::string_view name) {
    SD_CORE_ASSERT(m_sprites.find(name) != m_sprites.end(),
                   "Sprite {} not found!", name);
    return m_sprites.find(name)->second;
}

Texture &ResourceManager::getTexture(const std::string_view name) {
    SD_CORE_ASSERT(m_textures.find(name) != m_textures.end(),
                   "Texture {} not found!", name);
    return m_textures[name];
}

} // namespace Smedja

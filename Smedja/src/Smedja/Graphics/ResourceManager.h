/**
 * @file    ResourceManager.h
 * @brief   ResourceManager class
 */

#pragma once
#include "Smedja/Graphics/RectPacker.h"
#include "Smedja/Graphics/Sprite.h"
#include "Smedja/Graphics/Texture.h"
#include "Smedja/Graphics/TextureAtlas.h"
#include <glm/glm.hpp>

#include "pch.h"

namespace Smedja {

/**
 * @class ResourceManager
 * @brief ResourceManager is responsible for loading textures and creating
 *        sprites.
 *
 * ResourceManager is a singleton class. Sprites are created, managed, and
 * destroyed by the ResourceManager. The ResourceManager also holds textures
 * and texture atlases. It is responsible for gracefully reloading texture
 * atlases when textures are added or removed or when requested.
 *
 * @note Will eventually replace strings with UUID after implementing editor
 */
class ResourceManager {
public:
    /**
     * @brief Returns the singleton instance of ResourceManager.
     */
    // static ResourceManager &instance();

    /**
     * @brief Reloads texture atlases from held textures and sets sprites
     *        accordingly.
     */
    static void reload();

    static void addTexture(const std::string_view name,
                           const std::string &path);

    static void createSprite(const std::string_view name,
                             const std::string_view texture);
    static void createSprite(const std::string_view name);

    static void setSpriteTexture(const std::string_view spriteName,
                                 const std::string_view textureName);

    static void removeSprite(const std::string_view name);

    static void removeTexture(const std::string_view name);

    static Sprite &getSprite(const std::string_view name);

    static Texture &getTexture(const std::string_view name);

private:
    ResourceManager() = delete;
    // ResourceManager(const ResourceManager &);
    // ResourceManager operator=(const ResourceManager &);

private:
    static inline std::unordered_map<std::string_view, Texture> m_textures;
    static inline std::unordered_map<std::string_view, Sprite> m_sprites;
    static inline std::unordered_map<std::string_view, std::string_view>
        m_spriteToTextureMap;
    // std::vector<TextureAtlas> m_textureAtlases;
};

} // namespace Smedja

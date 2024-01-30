/**
 * @file	TextureAtlas.h
 * @brief	TextureAtlas class
 */

#pragma once
#include "Smedja/Graphics/Texture.h"
#include "pch.h"

namespace Smedja {

/**
 * @class TextureAtlas
 * @brief Child class of Texture. TextureAtlas is a texture that holds multiple
 *		  textures. It has the subimage utility method.
 */
class TextureAtlas : public Texture {
public:
    void subImage(const Texture &other, int x, int y);
};

}

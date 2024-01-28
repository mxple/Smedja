#pragma once
// #ifdef DEBUG
// #define STBI_NO_SIMD
// #endif
// #define STB_IMAGE_IMPLEMENTATION
// #include <stb_image.h>
#include "Smedja/Graphics/Texture.h"
#include "pch.h"

namespace Smedja {

class TextureAtlas : public Texture {
public:
	TextureAtlas();
	// Create texture atlas from cached texture file + json file
	// TextureAtlas(const std::string &texturePath, const std::string &jsonPath);
	~TextureAtlas();

	void reload();

	void addTexture(const std::string &name, const std::string &path);

	const std::shared_ptr<Texture> &texture() const;

private:



};

}

#include "Smedja/Renderer/GLTexture.h"
#include "glm/glm.hpp"
#include "pch.h"

namespace Smedja {

// Sprites are responsible for managing texel coords based of a texture atlas
// It may also hold data for collision detection, but that is not implemented
class Sprite {
public:
	Sprite(const glm::vec2 &texCoord1, const glm::vec2 &texCoord2,
	       const glm::vec2 &origin, const glm::vec2 &size);
	~Sprite();

	void setTexCoord1(const glm::vec2 &texCoord1);
	void setTexCoord2(const glm::vec2 &texCoord2);
	void setOrigin(const glm::vec2 &origin);
	void setSize(const glm::vec2 &size);

	const glm::vec2 &texCoord1() const;
	const glm::vec2 &texCoord2() const;
	const glm::vec2 &origin() const;
	const glm::vec2 &size() const;

private:
	glm::vec2 m_texCoord1;
	glm::vec2 m_texCoord2;
	glm::vec2 m_origin;
	glm::vec2 m_size;
	std::shared_ptr<GLTexture> m_textureAtlas;
};

} // namespace Smedja

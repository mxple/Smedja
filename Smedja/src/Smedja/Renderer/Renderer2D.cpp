#include "Renderer2D.h"
#include <glm/ext/matrix_transform.hpp>

namespace Smedja {

void Renderer2D::init() {
    // Create shaders
    Renderer2D::s_textureShader = std::make_shared<Shader>(
        "data/shaders/texture.vert", "data/shaders/texture.frag");

    // Create texture
    Renderer2D::s_whiteTexture = std::make_shared<Texture>();
    unsigned int whiteTextureData = 0xffffffff;
    Renderer2D::s_whiteTexture->setData((unsigned char *)&whiteTextureData, 1,
                                        1, GL_RGBA);

    // Bind texture (temp)
    Renderer2D::s_whiteTexture->bind();
    Renderer2D::s_textureShader->bind();
    Renderer2D::s_textureShader->setUniform1i("uTexture", 0);

    glGenBuffers(1, &s_quadSSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, s_quadSSBO);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, s_quadSSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER,
                 Renderer2D::maxQuads * sizeof(QuadData), nullptr,
                 GL_DYNAMIC_DRAW);
}

void Renderer2D::beginScene() {
    s_quads.clear();
}

void Renderer2D::endScene() {
    flush();
}

void Renderer2D::flush() {
    s_textureShader->bind();
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, s_quadSSBO);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0,
                    s_quads.size() * sizeof(QuadData),
                    (const void *)s_quads.data());
    glDrawElements(GL_TRIANGLES, s_quads.size() * 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer2D::drawQuadExt(const float x, const float y, const float width,
                             const float height, const float rotation,
                             const glm::vec4 &color,
                             const std::shared_ptr<Texture> &texture,
                             const glm::vec2 &texCoord1,
                             const glm::vec2 &texCoord2) {
    if (s_quads.size() >= Renderer2D::maxQuads) {
        endScene();
        beginScene();
    }
    // TODO: implement texture atlas, translate texcoords to atlas coords

    QuadData quadData;
    quadData.position = {x, y, 0}; // z default 0 right now
    quadData.size = {width, height};
    quadData.rotation = rotation;
    quadData.tintCol = color;
    quadData.texCoord1 = texCoord1;
    quadData.texCoord2 = texCoord2;

    s_quads.push_back(std::move(quadData)); // TODO: check move work
}

} // namespace Smedja

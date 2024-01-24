#include "Renderer2D.h"
#include <glm/ext/matrix_transform.hpp>

namespace Smedja {

void Renderer2D::init() {
    if (s_initialized) {
        SD_CORE_WARN("Renderer2D already initialized!");
        return;
    }
    s_initialized = true;

    // Create vertex array
    Renderer2D::s_vao = std::make_shared<VertexArray>();

    // Create index buffer 
    unsigned int *indices = new unsigned int[Renderer2D::maxQuads * 6];
    unsigned int offset = 0;
    for (int i = 0; i < Renderer2D::maxQuads * 6; i += 6) {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;

        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;

        offset += 4;
    }
    std::shared_ptr<IndexBuffer> ibo =
        std::make_shared<IndexBuffer>(indices, Renderer2D::maxQuads * 6);

    s_vao->setIndexBuffer(ibo);

    delete[] indices;

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
    SD_CORE_ASSERT(s_initialized, "Renderer2D not initialized!");
    s_quads.clear();
}

void Renderer2D::endScene() {
    SD_CORE_ASSERT(s_initialized, "Renderer2D not initialized!");
    flush();
}

void Renderer2D::flush() {
    s_vao->bind();
    s_whiteTexture->bind();
    s_textureShader->bind();
    s_textureShader->setUniform1i("uTexture", 0);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, s_quadSSBO);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0,
                    s_quads.size() * sizeof(QuadData),
                    (const void *)s_quads.data());
    glDrawElements(GL_TRIANGLES, s_quads.size() * 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer2D::drawQuadExt(const glm::vec3 &position, const glm::vec2 &size,
                             const float rotation, const glm::vec4 &color,
                             const std::shared_ptr<Texture> &texture,
                             const glm::vec2 &texCoord1,
                             const glm::vec2 &texCoord2) {
    if (s_quads.size() >= Renderer2D::maxQuads) {
        endScene();
        beginScene();
    }
    // TODO: implement texture atlas, translate texcoords to atlas coords

    QuadData quadData;
    quadData.position_rotation = {position, rotation};
    quadData.size_origin = {size, 0, 0};
    quadData.tintCol = color;
    quadData.texCoord1 = texCoord1;
    quadData.texCoord2 = texCoord2;

    s_quads.push_back(std::move(quadData)); // TODO: check move work
}

} // namespace Smedja

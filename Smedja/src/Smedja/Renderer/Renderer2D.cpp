#include "Renderer2D.h"

namespace Smedja {

void Renderer2D::init() {
    // Create vertex array
    Renderer2D::s_vao = std::make_shared<VertexArray>();

    // Create index buffer and bind to VAO
    unsigned int *quadIndices = new unsigned int[Renderer2D::maxIndices];

    int offset = 0;
    for (int i = 0; i < Renderer2D::maxIndices; i += 6) {
        quadIndices[i + 0] = offset + 0;
        quadIndices[i + 1] = offset + 1;
        quadIndices[i + 2] = offset + 2;
        quadIndices[i + 3] = offset + 2;
        quadIndices[i + 4] = offset + 3;
        quadIndices[i + 5] = offset + 0;
        offset += 4;
    }

    std::shared_ptr<IndexBuffer> quadEBO =
        std::make_shared<IndexBuffer>(quadIndices, Renderer2D::maxIndices);
    Renderer2D::s_vao->setIndexBuffer(quadEBO);

    delete[] quadIndices;

    // Create vertex buffer and bind to s_vao
    Renderer2D::s_vbo = std::make_shared<VertexBuffer>(Renderer2D::maxVertices *
                                                       sizeof(QuadVertex));
    s_quadVertexBufferBase = new QuadVertex[Renderer2D::maxVertices];

    BufferLayout layout = {
        {ShaderDataType::Float3},
        {ShaderDataType::Float4},
        {ShaderDataType::Float2},
    };
    Renderer2D::s_vbo->setLayout(layout);

    Renderer2D::s_vao->addVertexBuffer(Renderer2D::s_vbo);

    // Create white texture
    unsigned int whiteTextureData = 0xffffffff;
    Renderer2D::s_whiteTexture =
        std::make_shared<Texture>();
    Renderer2D::s_whiteTexture->setData((unsigned char *)&whiteTextureData,
                                        1, 1, GL_RGBA);

    // Create shaders
    // Renderer2D::s_colorShader = std::make_shared<Shader>(
    //     "data/shaders/color.vert", "data/shaders/color.frag");
    Renderer2D::s_textureShader = std::make_shared<Shader>(
        "data/shaders/texture.vert", "data/shaders/texture.frag");

    s_textureShader->bind();
    s_textureShader->setUniform1i("u_texture", 0);
}

void Renderer2D::beginScene() {
    s_textureShader->bind();
    s_quadVertexBufferPtr = s_quadVertexBufferBase;
    s_quadIndexCount = 0;
}

void Renderer2D::endScene() {
    int dataSize = (uint8_t *)s_quadVertexBufferPtr -
                   (uint8_t *)s_quadVertexBufferBase;
    s_vbo->setData((float *)s_quadVertexBufferBase, dataSize);
    flush();
}

void Renderer2D::flush() {
    s_textureShader->bind();
    s_vao->bind();
    s_whiteTexture->bind();

    glDrawElements(GL_TRIANGLES, s_quadIndexCount, GL_UNSIGNED_INT, nullptr);
}

void drawQuad() {

}

} // namespace Smedja

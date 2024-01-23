#include "Smedja/Renderer/Renderer.h"
#include "Smedja/Renderer/Shader.h"
#include "Smedja/Renderer/Texture.h"
#include "Smedja/Renderer/VertexArray.h"

namespace Smedja {

class Renderer2D {
public:
    static void init();

    static void beginScene();
    static void endScene();

    static void flush();

    // primitives
    static void drawQuad();

    // primitives but gui. separate functions to avoid global state

private:
    struct QuadVertex {
        glm::vec3 position;
        glm::vec4 color;
        glm::vec2 texCoord;
    };

    const static int maxQuads = 10000;
    const static int maxVertices = maxQuads * 4;
    const static int maxIndices = maxQuads * 6;
    
    static std::shared_ptr<VertexArray> s_vao;
    static std::shared_ptr<VertexBuffer> s_vbo;

    static std::shared_ptr<Texture> s_whiteTexture;

    static std::shared_ptr<Shader> s_textureShader;
    // static std::shared_ptr<Shader> s_colorShader;

    static QuadVertex *s_quadVertexBufferBase;
    static QuadVertex *s_quadVertexBufferPtr;

    static int s_quadIndexCount;
};

} // namespace Smedja

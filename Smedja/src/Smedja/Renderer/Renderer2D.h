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
    static void drawQuadExt(const float x, const float y, const float width,
                            const float height, const float rotation = 0.0f,
                            const glm::vec4 &color = {1.0f, 1.0f, 1.0f, 1.0f},
                            const std::shared_ptr<Texture> &texture = nullptr,
                            const glm::vec2 &texCoord1 = {0.0f, 0.0f},
                            const glm::vec2 &texCoord2 = {1.0f, 1.0f});

private:
    struct QuadData {
        glm::vec3 position;
        glm::vec2 size;
        float rotation;
        glm::vec4 tintCol;
        glm::vec2 texCoord1;
        glm::vec2 texCoord2;
    };

    const static int maxQuads = 10000;

    inline static std::vector<QuadData> s_quads = std::vector<QuadData>();
    inline static unsigned int s_quadSSBO = 0;

    // static std::shared_ptr<VertexArray> s_vao;
    inline static std::shared_ptr<Texture> s_whiteTexture = nullptr;

    inline static std::shared_ptr<Shader> s_textureShader = nullptr;
};

} // namespace Smedja

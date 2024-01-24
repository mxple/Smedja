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
    static void drawQuadExt(const glm::vec3 &position, const glm::vec2 &size,
                            const float rotation = 0.0f,
                            const glm::vec4 &color = {1.0f, 1.0f, 1.0f, 1.0f},
                            const std::shared_ptr<Texture> &texture = nullptr,
                            const glm::vec2 &texCoord1 = {0.0f, 0.0f},
                            const glm::vec2 &texCoord2 = {1.0f, 1.0f});

private:
    // 64 byte aligned struct for gpu to munch on
    struct QuadData {
        glm::vec4 position_rotation;
        glm::vec4 size_origin;
        glm::vec4 tintCol;
        glm::vec2 texCoord1;
        glm::vec2 texCoord2;
    };

    const static int maxQuads = 10000;

    inline static std::vector<QuadData> s_quads = std::vector<QuadData>();
    inline static unsigned int s_quadSSBO = 0;

    inline static std::shared_ptr<VertexArray> s_vao = nullptr;

    inline static std::shared_ptr<Texture> s_whiteTexture = nullptr;

    inline static std::shared_ptr<Shader> s_textureShader = nullptr;

    inline static bool s_initialized = false;
};

} // namespace Smedja

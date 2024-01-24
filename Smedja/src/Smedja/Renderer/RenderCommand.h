#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Smedja {

// gl abstraction interface for functions shared between 2D and 3D renderer
class RenderCommand {
public:
    static void init() {
        // glEnable(GL_DEPTH_TEST);  
        glEnable(GL_BLEND);  
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    static void setClearColor(float r, float g, float b, float a) {
        glClearColor(r, g, b, a);
    }

    static void setClearColor(glm::vec4 color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    static void clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    static void setViewport(int x, int y, int width, int height) {
        glViewport(x, y, width, height);
    }
};

}

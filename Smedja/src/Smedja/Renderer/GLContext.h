#include "GLFW/glfw3.h"

namespace Smedja {

class GLContext { 
public:
    GLContext(GLFWwindow* window);

    void init();
    void swapBuffers();

private:
    GLFWwindow* m_windowHandle;

};

} // namespace Smedja

#include "GLContext.h"
#include "pch.h"
#include <glad/glad.h>

namespace Smedja {

GLContext::GLContext(GLFWwindow* window) : m_windowHandle(window) {}

void GLContext::init() {
    glfwMakeContextCurrent(m_windowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    SD_CORE_ASSERT(status, "Failed to initialize glad!");
}

void GLContext::swapBuffers() {
    glfwSwapBuffers(m_windowHandle);
}

}

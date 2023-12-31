#pragma once

#include "GLFW/glfw3.h"
#include "pch.h"

namespace Smedja {

class Window;   // Forward declaration for friend class

// Responsible for input polling
class Input {
public:
    static bool isKeyPressed(int keycode) {
        CORE_ASSERT(s_window, "Window is null!")
        auto state = glfwGetKey(s_window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    static bool isMouseButtonPressed(int button) {
        CORE_ASSERT(s_window, "Window is null!")
        auto state = glfwGetMouseButton(s_window, button);
        return state == GLFW_PRESS;
    }

    static std::pair<float, float> getMousePosition() {
        CORE_ASSERT(s_window, "Window is null!")
        double xpos, ypos;
        glfwGetCursorPos(s_window, &xpos, &ypos);
        return {static_cast<float>(xpos), static_cast<float>(ypos)};
    }

    static float getMouseX() {
        CORE_ASSERT(s_window, "Window is null!")
        return getMousePosition().first;
    }
    
    static float getMouseY() {
        CORE_ASSERT(s_window, "Window is null!")
        return getMousePosition().second;
    }

protected:
    friend Window;
    inline static GLFWwindow *s_window = nullptr;
};

} // namespace Smedja


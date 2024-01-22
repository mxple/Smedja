#pragma once

// #include <GLFW/glfw3.h>

#include "Smedja/Events/Event.h"
#include "Smedja/Core/Input.h"
#include "Smedja/Renderer/GLContext.h"
#include "pch.h"

namespace Smedja {

// Window data
struct WindowProps {
    std::string title;
    unsigned int width;
    unsigned int height;

    WindowProps(const std::string &title = "Smedja Engine",
                unsigned int width = 1280, unsigned int height = 720)
        : title(title), width(width), height(height) {}
};

class Window {
public:
    using EventCallbackFn = std::function<void(Event &)>;

    Window();
    Window(const WindowProps &props);
    virtual ~Window();

    void onUpdate();

    inline unsigned int getWidth() const {
        return m_Data.width;
    }
    inline unsigned int getHeight() const {
        return m_Data.height;
    }

    // Window attributes
    inline void setEventCallback(const EventCallbackFn &callback) {
        m_Data.eventCallback = callback;
    }
    void setVSync(bool enabled);
    bool isVSync() const;

    void setFocus(bool focus) {
        m_focused = focus;
    }

    bool getFocus() const {
        return m_focused;
    }

    inline void *getGLFWWindow() const {
        return m_window;
    }
    // static Window* create(const WindowProps& props = WindowProps());

private:
    void init(const WindowProps &props);
    void shutdown();

    GLFWwindow *m_window;
    GLContext* m_graphicsContext;

    struct WindowData {
        std::string title;
        unsigned int width;
        unsigned int height;
        bool vSync;

        EventCallbackFn eventCallback;
    };

    WindowData m_Data;
    bool m_focused = true;
};

} // namespace Smedja

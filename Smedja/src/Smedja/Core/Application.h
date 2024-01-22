#pragma once

#include "Smedja/Events/ApplicationEvent.h"
#include "Smedja/Events/Event.h"
#include "Smedja/Core/LayerStack.h"
#include "Smedja/Renderer/Buffer.h"
#include "Smedja/Renderer/Shader.h"
#include "Smedja/Renderer/Texture.h"
#include "Smedja/Renderer/VertexArray.h"
#include "Smedja/Core/Window.h"

namespace Smedja {

class Application {
public:
    Application();
    virtual ~Application();

    inline static Application& get() { return *s_instance; }
    inline Window& getWindow() { return *m_Window; }

    void run();

    void onEvent(Event &e);

    void pushLayer(Layer *layer);
    void pushOverlay(Layer *overlay);

    void popLayer(Layer *layer);
    void popOverlay(Layer *overlay);

private:
    bool onWindowClose(WindowCloseEvent &e);
    bool onWindowFocus(WindowFocusEvent &e);
    bool onWindowLostFocus(WindowLostFocusEvent &e);

    static Application* s_instance;

    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
    bool m_focused = true;
    LayerStack m_layerStack;

    float m_lastFrameTime;
};

// To be defined in client
Application *createApplication();

} // namespace Smedja

#include "Application.h"

#include <glad/glad.h>

#include "Smedja/Input.h"
#include "pch.h"

namespace Smedja {

Application *Application::s_instance = nullptr;

Application::Application() {
    SD_CORE_ASSERT(!s_instance, "Application already exists!");
    s_instance = this;
    m_Window = std::unique_ptr<Window>(new Window());
    m_Window->setEventCallback(SD_BIND_EVENT_FN(Application::onEvent));
}

Application::~Application() {}

void Application::run() {
    SD_CORE_INFO("Ready to run!");

    while (m_Running) {
        if (m_focused) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            for (Layer *layer : m_layerStack) {
                layer->onUpdate();
            }
        }

        m_Window->onUpdate();
    }
}

void Application::pushLayer(Layer *layer) {
    m_layerStack.pushLayer(layer);
}

void Application::pushOverlay(Layer *overlay) {
    m_layerStack.pushOverlay(overlay);
}

void Application::popLayer(Layer *layer) {
    m_layerStack.popLayer(layer);
}

void Application::popOverlay(Layer *overlay) {
    m_layerStack.popLayer(overlay);
}

void Application::onEvent(Event &e) {
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>(
        SD_BIND_EVENT_FN(Application::onWindowClose));
    dispatcher.dispatch<WindowFocusEvent>(
        SD_BIND_EVENT_FN(Application::onWindowFocus));
    dispatcher.dispatch<WindowLostFocusEvent>(
        SD_BIND_EVENT_FN(Application::onWindowLostFocus));

    for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
        (*--it)->onEvent(e);

        // Prevent layer beneath from recieving handeled event
        if (!e.isHandled()) {
            break;
        }
    }
}

// Event functions
bool Application::onWindowClose(WindowCloseEvent &e) {
    m_Running = false;
    return true;
}

bool Application::onWindowFocus(WindowFocusEvent &e) {
    m_focused = true;
    return true;
}

bool Application::onWindowLostFocus(WindowLostFocusEvent &e) {
    m_focused = false;
    return true;
}

} // namespace Smedja

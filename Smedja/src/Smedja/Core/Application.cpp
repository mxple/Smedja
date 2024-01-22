#include "Application.h"

#include <glad/glad.h>

#include "Smedja/Core/Time.h"
#include "Smedja/Core/Input.h"
#include "Smedja/Renderer/RenderCommand.h"
#include "pch.h"

namespace Smedja {

Application *Application::s_instance = nullptr;

Application::Application() {
    SD_CORE_ASSERT(!s_instance, "Application already exists!");
    s_instance = this;
    m_Window = std::unique_ptr<Window>(new Window());
    m_Window->setEventCallback(SD_BIND_EVENT_FN(Application::onEvent));

    m_lastFrameTime = (float)glfwGetTime();
}

Application::~Application() {}

void Application::run() {
    SD_CORE_INFO("Ready to run!");

    while (m_Running) {
        if (m_focused) {
            float time = (float)glfwGetTime();
            TimeStep deltaTime = time - m_lastFrameTime;
            m_lastFrameTime = time;

            RenderCommand::setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            RenderCommand::clear();

            for (Layer *layer : m_layerStack) {
                layer->onUpdate(deltaTime);
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

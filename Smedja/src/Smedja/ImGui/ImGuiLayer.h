#pragma once

#include "Smedja/Events/CharTypedEvent.h"
#include "Smedja/Layer.h"
#include "Smedja/Events/ApplicationEvent.h"
#include "Smedja/Events/KeyEvent.h"
#include "Smedja/Events/MouseEvent.h"
#include "Smedja/Events/Event.h"

#include "imgui.h"

namespace Smedja {

class ImGuiLayer : public Layer { 
public:
    ImGuiLayer();
    ~ImGuiLayer();

    virtual void onAttach() override;
    virtual void onDetach() override;

    virtual void onUpdate(TimeStep &deltaTime) override;
    virtual void onEvent(Event& e) override;

private:
    bool onMouseButtonPressedEvent(MouseButtonPressedEvent& e);
    bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
    bool onMouseMovedEvent(MouseMovedEvent& e);
    bool onMouseScrolledEvent(MouseScrolledEvent& e);
    bool onKeyPressedEvent(KeyPressedEvent& e);
    bool onKeyReleasedEvent(KeyReleasedEvent& e);
    bool onCharTypedEvent(CharTypedEvent& e);
    bool onWindowResizeEvent(WindowResizeEvent& e);
    bool onWindowFocusEvent(WindowFocusEvent& e);
    bool onWindowLostFocusEvent(WindowLostFocusEvent &e);

    static ImGuiKey convertGLFWKeyCodeToImGuiKeyCode(int keycode);

    bool m_showDemoWindow = false;
    bool m_renderImGui = true;
};

}

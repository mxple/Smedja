#pragma once

#include "Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace Smedja {

class Application {
public:
    Application();
    virtual ~Application();

    void run();

    void onEvent(Event& e);

private:
    bool onWindowClose(WindowCloseEvent& e);

    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
};

// To be defined in client
Application *createApplication();

} // namespace Smedja

#pragma once

#include "Window.h"

namespace Smedja {

class Application {
   public:
    Application();
    virtual ~Application();

    void run();

   private:
    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
};

// To be defined in client
Application* createApplication();

}  // namespace Smedja

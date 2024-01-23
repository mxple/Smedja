// #include "Smedja/ImGui/ImGuiLayer.h"
#include <Smedja.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TestLayer2D.h"

class Sandbox : public Smedja::Application {
public:
    Sandbox() {
        // pushLayer(new TestLayer());
        pushLayer(new TestLayer2D());
        pushOverlay(new Smedja::ImGuiLayer());
    }

    ~Sandbox() {}
};

Smedja::Application *Smedja::createApplication() {
    return new Sandbox();
}

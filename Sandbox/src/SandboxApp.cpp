// #include "Smedja/ImGui/ImGuiLayer.h"
#include <Smedja.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "TestLayer.h"

class Sandbox : public Smedja::Application {
public:
    Sandbox() {
        pushLayer(new TestLayer());
        pushOverlay(new Smedja::ImGuiLayer());
    }

    ~Sandbox() {}
};

Smedja::Application *Smedja::createApplication() {
    return new Sandbox();
}

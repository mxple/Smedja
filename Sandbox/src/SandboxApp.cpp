// #include "Smedja/ImGui/ImGuiLayer.h"
#include <Smedja.h>

class TestLayer : public Smedja::Layer {
public:
    TestLayer() : Layer("TestLayer") {}
    void onUpdate() override {
        SD_TRACE("{} updating", m_debugName);
    }

    void onEvent(Smedja::Event &e) override {
        SD_TRACE("{0} recieved event: {1}", m_debugName, e);
    }
};

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

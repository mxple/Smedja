// #include "Smedja/ImGui/ImGuiLayer.h"
#include <Smedja.h>

class TestLayer : public Smedja::Layer {
public:
    TestLayer() : Layer("TestLayer") {}
    void onUpdate() override {
    }

    void onEvent(Smedja::Event &e) override {
    }
};

class Sandbox : public Smedja::Application {
public:
    Sandbox() {
        pushOverlay(new Smedja::ImGuiLayer());
    }

    ~Sandbox() {}
};

Smedja::Application *Smedja::createApplication() {
    return new Sandbox();
}

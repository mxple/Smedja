#include <Smedja.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TestLayer2D : public Smedja::Layer {
public:
    TestLayer2D() : Layer("TestLayer"), m_cameraController(m_camera) {
        Smedja::ResourceManager::addTexture("t_metal_crate", "data/metal_crate.png");
        Smedja::ResourceManager::createSprite("s_metal_crate", "t_metal_crate");
        Smedja::ResourceManager::reload();
    }
    void onUpdate(Smedja::TimeStep &deltaTime) override {
        m_cameraController.onUpdate(deltaTime);

        Smedja::Renderer2D::beginScene();

        // takes ~10ms to render 100000 quads
        for (int i = 0; i < 100000; i++) {
            Smedja::Renderer2D::drawQuadExt({i * 0.001f, 0.0f, 0.0f}, {0.01f, 0.01f});
        }
        Smedja::Renderer2D::drawSprite(Smedja::ResourceManager::getSprite("s_metal_crate"), {0.0f, 0.0f, 0.0f}, {0.5f, 0.5f});

        Smedja::Renderer2D::endScene();
    }

    void onEvent(Smedja::Event &e) override {
        m_cameraController.onEvent(e);
    }

private:
    Smedja::EuclideanCamera m_camera;
    Smedja::CameraController m_cameraController;
};



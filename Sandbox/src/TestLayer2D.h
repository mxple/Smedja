#include <Smedja.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TestLayer2D : public Smedja::Layer {
public:
    TestLayer2D() : Layer("TestLayer"), m_cameraController(m_camera) {
    }
    void onUpdate(Smedja::TimeStep &deltaTime) override {
        m_cameraController.onUpdate(deltaTime);

        Smedja::Renderer2D::beginScene();

        Smedja::Renderer2D::drawQuadExt(0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
                                        {0.2f, 0.3f, 0.8f, 1.0f});
        // Smedja::Renderer2D::drawQuadExt(0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
        //                                 {0.8f, 0.3f, 0.2f, 1.0f});
        // Smedja::Renderer2D::drawQuadExt(-0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
        //                                 {0.2f, 0.8f, 0.3f, 1.0f});
        // Smedja::Renderer2D::drawQuadExt(-0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
        //                                 {0.8f, 0.2f, 0.3f, 1.0f});

        Smedja::Renderer2D::endScene();
    }

    void onEvent(Smedja::Event &e) override {
        m_cameraController.onEvent(e);
    }

private:
    Smedja::EuclideanCamera m_camera;
    Smedja::CameraController m_cameraController;
};



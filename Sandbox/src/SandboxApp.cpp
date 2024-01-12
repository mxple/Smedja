// #include "Smedja/ImGui/ImGuiLayer.h"
#include <Smedja.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TestLayer : public Smedja::Layer {
public:
    TestLayer() : Layer("TestLayer"), m_cameraController(m_camera) {
        float vertices[] = {
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        unsigned int indices[] = {
             0,  1,  2,  2,  3,  0,
             4,  5,  6,  6,  7,  4,
             8,  9, 10, 10, 11,  8,
            12, 13, 14, 14, 15, 12,
            16, 17, 18, 18, 19, 16,
            20, 21, 22, 22, 23, 20
        };
        Smedja::BufferLayout layout = {
            {Smedja::ShaderDataType::Float3},   // positionns
            {Smedja::ShaderDataType::Float2},   // texture coords
        };
        
        m_shader.reset(new Smedja::Shader("data/shaders/test.vert", "data/shaders/test.frag"));
        m_texture1.reset(new Smedja::Texture("data/metal_crate.png"));
        m_texture2.reset(new Smedja::Texture("data/metal_crate_normal.png"));

        m_vertexArray.reset(new Smedja::VertexArray());
        m_vertexBuffer.reset(new Smedja::VertexBuffer(vertices, sizeof(vertices)));
        m_indexBuffer.reset(new Smedja::IndexBuffer(indices, sizeof(indices)));

        m_vertexBuffer->setLayout(layout);  // move occurs ( in theory )

        m_vertexArray->addVertexBuffer(m_vertexBuffer);
        m_vertexArray->setIndexBuffer(m_indexBuffer);
    }
    void onUpdate() override {
        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f), 
            glm::vec3( 2.0f,  5.0f, -15.0f), 
            glm::vec3(-1.5f, -2.2f, -2.5f),  
            glm::vec3(-3.8f, -2.0f, -12.3f),  
            glm::vec3( 2.4f, -0.4f, -3.5f),  
            glm::vec3(-1.7f,  3.0f, -7.5f),  
            glm::vec3( 1.3f, -2.0f, -2.5f),  
            glm::vec3( 1.5f,  2.0f, -2.5f), 
            glm::vec3( 1.5f,  0.2f, -1.5f), 
            glm::vec3(-1.3f,  1.0f, -1.5f)  
        };
        // transforms and camera!
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        float time = glfwGetTime();
        glm::vec3 axis(1.0f, 0.0f, 0.0f);

        // Rotation angle based on time (adjust the speed as needed)
        float rotationSpeed = 1.0f; // Adjust as needed
        float angle = rotationSpeed * time;

        // Create a rotation matrix using GLM
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));

        // Apply the rotation to the original vector
        axis = glm::vec4(axis, 1.0f) * rotationMatrix;

        projection = glm::perspective(glm::radians(45.0f), 
                                      (float)Smedja::Application::get().getWindow().getWidth() / 
                                      (float)Smedja::Application::get().getWindow().getHeight(),
                                      0.1f, 100.0f);

        // draw triangle!
        m_shader->bind();

        m_shader->setUniformMat4x4("uView", m_cameraController.getCamera().getView());
        m_shader->setUniformMat4x4("uProjection", projection);

        m_texture1->bind(0);
        m_texture2->bind(1);

        m_shader->setUniform1i("uTexture1", 0);
        m_shader->setUniform1i("uTexture2", 1);
        m_vertexArray->bind();
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i; 
            model = glm::rotate(model, time + angle, axis);
            m_shader->setUniformMat4x4("uModel", model);

            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
    }

    void onEvent(Smedja::Event &e) override {
    }

private:
    std::shared_ptr<Smedja::VertexArray> m_vertexArray;
    std::shared_ptr<Smedja::VertexBuffer> m_vertexBuffer;
    std::shared_ptr<Smedja::IndexBuffer> m_indexBuffer;
    std::shared_ptr<Smedja::Shader> m_shader;
    std::shared_ptr<Smedja::Texture> m_texture1;
    std::shared_ptr<Smedja::Texture> m_texture2;
    Smedja::EuclideanCamera m_camera;
    Smedja::CameraController m_cameraController;
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

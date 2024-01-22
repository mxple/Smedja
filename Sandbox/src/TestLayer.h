#include <Smedja.h>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TestLayer : public Smedja::Layer {
public:
    TestLayer() : Layer("TestLayer"), m_cameraController(m_camera) {
        // cube
        float vertices[] = {
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f, 0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f, 0.0f, -1.0f,

             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, 0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f, 0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   0.0f, 0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f, 0.0f,  1.0f,

            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   -1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   -1.0f, 0.0f, 0.0f,

             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   1.0f, 0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,

             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,   0.0f, -1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f, 0.0f,

             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f, 1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,   0.0f, 1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f, 1.0f, 0.0f,
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
            {Smedja::ShaderDataType::Float3},   // normals
        };

        m_shader.reset(new Smedja::Shader("data/shaders/default.vert", "data/shaders/lightTarget.frag"));
        m_lightingShader.reset(new Smedja::Shader("data/shaders/default.vert", "data/shaders/lightCube.frag"));
        m_texture1.reset(new Smedja::Texture("data/metal_crate.png"));

        m_cube.reset(new Smedja::VertexArray());
        m_vertexBuffer.reset(new Smedja::VertexBuffer(vertices, sizeof(vertices)));
        m_indexBuffer.reset(new Smedja::IndexBuffer(indices, sizeof(indices)));

        m_vertexBuffer->setLayout(layout);
        m_cube->addVertexBuffer(m_vertexBuffer);
        m_cube->setIndexBuffer(m_indexBuffer);
    }
    void onUpdate(Smedja::TimeStep &deltaTime) override {
        m_cameraController.onUpdate(deltaTime);

        // transforms and camera!
        glm::mat4 projection = glm::mat4(1.0f);

        float time = glfwGetTime();
        glm::vec3 axis(1.0f, 0.0f, 0.0f);

        // Rotation angle based on time (adjust the speed as needed)
        float rotationSpeed = .2f; // Adjust as needed
        float angle = rotationSpeed * time;

        // Create a rotation matrix using GLM
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));

        // Apply the rotation to the original vector
        axis = glm::vec4(axis, 1.0f) * rotationMatrix;

        projection = glm::perspective(glm::radians(45.0f),
                                      (float)Smedja::Application::get().getWindow().getWidth() /
                                      (float)Smedja::Application::get().getWindow().getHeight(),
                                      0.1f, 100.0f);

        glm::vec3 lightPos(sin(time) * 2.0f, 0.0f, cos(time) * 2.0f);
        glm::vec3 lightColor(1.0f, 1.0f, 0.6f);

        m_cube->bind();

        // TODO texture abstraction
        m_texture1->bind(0);
        m_shader->setUniform1i("uTexture1", 0);

        glm::mat4 model = glm::rotate(glm::mat4(1.0), time + angle, axis);
        // glm::mat4 model = glm::mat4(1.);

        m_shader->bind();
        m_shader->setUniformMat4x4("uView", m_cameraController.getCamera().getView());
        m_shader->setUniformMat4x4("uProjection", projection);
        m_shader->setUniformMat4x4("uModel", model);

        m_shader->setUniform3f("uLightPos", lightPos);
        m_shader->setUniform3f("uLightColor", lightColor);
        m_shader->setUniform3f("uViewPos", m_cameraController.getCamera().getPos());

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        model = glm::translate(glm::mat4(1.0), lightPos);
        model = glm::scale(model, glm::vec3(0.2f));

        m_lightingShader->bind();
        m_lightingShader->setUniform3f("uLightColor", lightColor);
        m_lightingShader->setUniformMat4x4("uView", m_cameraController.getCamera().getView());
        m_lightingShader->setUniformMat4x4("uProjection", projection);
        m_lightingShader->setUniformMat4x4("uModel", model);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    void onEvent(Smedja::Event &e) override {
        m_cameraController.onEvent(e);
    }

private:
    std::shared_ptr<Smedja::VertexArray> m_cube;
    std::shared_ptr<Smedja::VertexBuffer> m_vertexBuffer;
    std::shared_ptr<Smedja::IndexBuffer> m_indexBuffer;
    std::shared_ptr<Smedja::Shader> m_shader;
    std::shared_ptr<Smedja::Shader> m_lightingShader;
    std::shared_ptr<Smedja::Texture> m_texture1;
    std::shared_ptr<Smedja::Texture> m_texture2;
    Smedja::EuclideanCamera m_camera;
    Smedja::CameraController m_cameraController;
};



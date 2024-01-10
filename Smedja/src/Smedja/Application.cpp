#include "Application.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Smedja/Input.h"
#include "pch.h"

namespace Smedja {

Application *Application::s_instance = nullptr;

Application::Application() {
    SD_CORE_ASSERT(!s_instance, "Application already exists!");
    s_instance = this;
    m_Window = std::unique_ptr<Window>(new Window());
    m_Window->setEventCallback(SD_BIND_EVENT_FN(Application::onEvent));

    // FIRST TRIANGLE (now square)
    float vertices[] = {
        // positions        // colors           // texture coords
        -0.5, -0.5, 0.0,    1.0, 0.0, 0.0,      0.0,  0.0,
        -0.5,  0.5, 0.0,    0.0, 1.0, 0.0,      0.0,  1.0,
         0.5, -0.5, 0.0,    0.0, 0.0, 1.0,      1.0,  0.0,
         0.5,  0.5, 0.0,    1.0, 1.0, 1.0,      1.0,  1.0,
    };
    unsigned int indices[] = {
        0, 1, 2,   // first triangle
        1, 2, 3    // second triangle
    };  

    m_shader.reset(new Shader("data/shaders/test.vert", "data/shaders/test.frag"));
    m_texture1.reset(new Texture("data/metal_crate.png"));
    m_texture2.reset(new Texture("data/metal_crate_normal.png"));

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    m_vertexBuffer.reset(new VertexBuffer(vertices, sizeof(vertices)));
    m_indexBuffer.reset(new IndexBuffer(indices, sizeof(indices)));

    m_vertexBuffer->bind();
    m_indexBuffer->bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    m_vertexBuffer->unbind();
}

Application::~Application() {}

void Application::run() {
    SD_CORE_INFO("Ready to run!");

    while (m_Running) {
        if (m_focused) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // transforms and camera!
            glm::mat4 model = glm::mat4(1.0f);
            glm::mat4 view = glm::mat4(1.0f);
            glm::mat4 projection = glm::mat4(1.0f);

            model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(0.0f, 0.0f, 1.0f));
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
            projection = glm::perspective(glm::radians(45.0f), (float)m_Window->getWidth() / (float)m_Window->getHeight(), 0.1f, 100.0f);

            // draw triangle!
            m_shader->bind();

            m_shader->setUniformMat4x4("uModel", model);
            m_shader->setUniformMat4x4("uView", view);
            m_shader->setUniformMat4x4("uProjection", projection);

            m_texture1->bind(0);
            m_texture2->bind(1);

            m_shader->setUniform1i("uTexture1", 0);
            m_shader->setUniform1i("uTexture2", 1);
            glBindVertexArray(m_VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            for (Layer *layer : m_layerStack) {
                layer->onUpdate();
            }
        }

        m_Window->onUpdate();
    }
}

void Application::pushLayer(Layer *layer) {
    m_layerStack.pushLayer(layer);
}

void Application::pushOverlay(Layer *overlay) {
    m_layerStack.pushOverlay(overlay);
}

void Application::popLayer(Layer *layer) {
    m_layerStack.popLayer(layer);
}

void Application::popOverlay(Layer *overlay) {
    m_layerStack.popLayer(overlay);
}

void Application::onEvent(Event &e) {
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<WindowCloseEvent>(
        SD_BIND_EVENT_FN(Application::onWindowClose));
    dispatcher.dispatch<WindowFocusEvent>(
        SD_BIND_EVENT_FN(Application::onWindowFocus));
    dispatcher.dispatch<WindowLostFocusEvent>(
        SD_BIND_EVENT_FN(Application::onWindowLostFocus));

    for (auto it = m_layerStack.end(); it != m_layerStack.begin();) {
        (*--it)->onEvent(e);

        // Prevent layer beneath from recieving handeled event
        if (!e.isHandled()) {
            break;
        }
    }
}

// Event functions
bool Application::onWindowClose(WindowCloseEvent &e) {
    m_Running = false;
    return true;
}

bool Application::onWindowFocus(WindowFocusEvent &e) {
    m_focused = true;
    return true;
}

bool Application::onWindowLostFocus(WindowLostFocusEvent &e) {
    m_focused = false;
    return true;
}

} // namespace Smedja

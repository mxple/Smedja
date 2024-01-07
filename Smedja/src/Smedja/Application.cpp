#include "Application.h"

#include <glad/glad.h>

#include "Smedja/Input.h"
#include "pch.h"

namespace Smedja {

Application *Application::s_instance = nullptr;

Application::Application() {
    SD_CORE_ASSERT(!s_instance, "Application already exists!");
    s_instance = this;
    m_Window = std::unique_ptr<Window>(new Window());
    m_Window->setEventCallback(SD_BIND_EVENT_FN(Application::onEvent));

    // FIRST TRIANGLE
    float vertices[] = {
        -0.5, -0.5, 0.0,
         0.5, -0.5, 0.0,
         0.0,  0.5, 0.0,
    };
    const char *vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        void main() {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )";
    const char *fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        } 
    )";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int  success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        SD_CORE_ERROR("{}", infoLog);
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        SD_CORE_ERROR("{}", infoLog);
    }

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(m_shaderProgram, 512, NULL, infoLog);
        SD_CORE_ERROR("{}", infoLog);
    }
    // glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexArrayAttrib(m_VAO, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   // unbind VBO

    glBindVertexArray(0);   // unbind VAO
}

Application::~Application() {}

void Application::run() {
    while (m_Running) {
        if (m_focused) {
            glClearColor(1, 1, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            // draw triangle!
            glUseProgram(m_shaderProgram);
            glBindVertexArray(m_VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

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

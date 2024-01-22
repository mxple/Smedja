#include "CameraController.h"
#include "Smedja/Core/Input.h"
#include "Smedja/Core/KeyCodes.h"
#include "Smedja/Core/MouseCodes.h"

namespace Smedja {

CameraController::CameraController(Camera &camera) : m_camera(camera) {}

void CameraController::onEvent(Event &e) {
    EventDispatcher dispatcher(e);
    dispatcher.dispatch<MouseMovedEvent>(
        SD_BIND_EVENT_FN(CameraController::onMouseMoved));
    dispatcher.dispatch<MouseScrolledEvent>(
        SD_BIND_EVENT_FN(CameraController::onMouseScrolled));
    dispatcher.dispatch<WindowResizeEvent>(
        SD_BIND_EVENT_FN(CameraController::onWindowResized));
}

void CameraController::onUpdate(TimeStep &deltaTime) {
    float velocity = m_moveSpeed * (float)deltaTime;
    if (Input::isKeyPressed(SD_KEY_W)) {
        m_camera.m_pos += m_camera.m_front * velocity;
    } else if (Input::isKeyPressed(SD_KEY_S)) {
        m_camera.m_pos -= m_camera.m_front * velocity;
    }

    // TODO see if we want to use camera.m_right instead of cross product
    if (Input::isKeyPressed(SD_KEY_A)) {
        m_camera.m_pos -=
            glm::normalize(glm::cross(m_camera.m_front, m_camera.m_up)) *
            velocity;
    } else if (Input::isKeyPressed(SD_KEY_D)) {
        m_camera.m_pos +=
            glm::normalize(glm::cross(m_camera.m_front, m_camera.m_up)) *
            velocity;
    }

    // if (Input::isKeyPressed(SD_KEY_Q)) {
    //     m_yaw -= m_moveSpeed;
    // } else if (Input::isKeyPressed(SD_KEY_E)) { 
    //     m_yaw += m_moveSpeed;
    // }
    //
    // if (Input::isKeyPressed(SD_KEY_SPACE)) {
    //     m_pitch += m_moveSpeed;
    // } else if (Input::isKeyPressed(SD_KEY_LEFT_SHIFT)) {
    //     m_pitch -= m_moveSpeed;
    // }
    //
    // glm::vec3 facingDirection;
    // facingDirection.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    // facingDirection.y = sin(glm::radians(m_pitch));
    // facingDirection.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    // m_camera.m_front = glm::normalize(facingDirection);

    m_camera.updateView();
}

bool CameraController::onMouseMoved(MouseMovedEvent &e) {
    if (!Input::isMouseButtonPressed(SD_MOUSE_BUTTON_2)) {
        m_mouseXLast = e.getX();
        m_mouseYLast = e.getY();
        return false;
    }

    // drag (inverted)
    float dx = m_mouseXLast - e.getX();
    float dy = e.getY() - m_mouseYLast; // glfw coords flipped
 
    // float dx = e.getX() - m_mouseXLast;
    // float dy = m_mouseYLast - e.getY(); // glfw coords flipped
    m_mouseXLast = e.getX();
    m_mouseYLast = e.getY();
    m_yaw += dx * m_sensitivity;
    m_pitch += dy * m_sensitivity;

    // https://www.symbolab.com/solver/matrix-multiply-calculator/%5Cleft(%5Cbegin%7Bpmatrix%7Dcos%5Cleft(a%5Cright)%26-sin%5Cleft(a%5Cright)%26%5C%5C%20%20%20%20%20sin%5Cleft(a%5Cright)%26cos%5Cleft(a%5Cright)%26%5C%5C%20%20%20%20%20%26%261%5Cend%7Bpmatrix%7D%5Cbegin%7Bpmatrix%7Dcos%5Cleft(b%5Cright)%26%26sin%5Cleft(b%5Cright)%5C%5C%20%20%20%20%20%261%26%5C%5C%20%20%20%20%20-sin%5Cleft(b%5Cright)%26%26cos%5Cleft(b%5Cright)%5Cend%7Bpmatrix%7D%5Cbegin%7Bpmatrix%7D1%260%260%5C%5C%20%200%261%260%5C%5C%20%200%260%261%5Cend%7Bpmatrix%7D%5Cright)?or=input
    glm::vec3 facingDirection;
    facingDirection.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    facingDirection.y = sin(glm::radians(m_pitch));
    facingDirection.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_camera.m_front = glm::normalize(facingDirection);
    m_camera.updateView();
    return false;
}

bool CameraController::onMouseScrolled(MouseScrolledEvent &e) {
    m_camera.m_fovDegree -= e.getYOffset();
    m_camera.m_fovDegree = glm::clamp(m_camera.m_fovDegree, 1.0f, 45.0f);
    m_camera.updateView();
    return false;
}

bool CameraController::onWindowResized(WindowResizeEvent &e) {
    m_camera.m_aspectRatio = (float)e.getWidth() / (float)e.getHeight();
    m_camera.updateView();
    return false;
}

} // namespace Smedja

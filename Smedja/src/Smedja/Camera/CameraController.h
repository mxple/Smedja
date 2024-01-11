#pragma once
#include <glm/glm.hpp>
#include "Smedja/Events/ApplicationEvent.h"
#include "Smedja/Events/MouseEvent.h"

#include "EuclideanCamera.h"

namespace Smedja {

template <typename CAM_TYPE>
class CameraController {
public:
    CameraController(glm::vec3 pos = {0, 0, 0}, glm::vec3 front = {0, 0, -1},
                     glm::vec3 up = {0, 1, 0});
    ~CameraController() = default;

    void onEvent(Event &e);

    void onUpdate();

    CAM_TYPE &getCamera() {
        return m_camera;
    }
    const CAM_TYPE &getCamera() const {
        return m_camera;
    }

private:
    // Event callbacks
    bool onMouseMoved(MouseMovedEvent &e);
    bool onMouseScrolled(MouseScrolledEvent &e);
    bool onWindowResized(WindowResizeEvent &e);

    // Euclidean or Quat
    CAM_TYPE m_camera;

    float m_yaw;
    float m_pitch;
    // float m_roll;

    // Control variables
    float m_sensitivity;
    float m_moveSpeed;
    float m_mouseXLast;
    float m_mouseYLast;
};

} // namespace Smedja

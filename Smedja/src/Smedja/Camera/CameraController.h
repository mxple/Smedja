#pragma once
#include <glm/glm.hpp>
#include "Smedja/Events/ApplicationEvent.h"
#include "Smedja/Events/MouseEvent.h"

#include "EuclideanCamera.h"

namespace Smedja {

class CameraController {
public:
    CameraController(Camera &camera);
    ~CameraController() = default;

    void onEvent(Event &e);

    void onUpdate();

    Camera &getCamera() {
        return m_camera;
    }
    const Camera &getCamera() const {
        return m_camera;
    }

private:
    // Event callbacks
    bool onMouseMoved(MouseMovedEvent &e);
    bool onMouseScrolled(MouseScrolledEvent &e);
    bool onWindowResized(WindowResizeEvent &e);

    // Euclidean or Quat
    Camera &m_camera;

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

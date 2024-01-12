#pragma once
#include <glm/glm.hpp>
#include "Smedja/Core/Time.h"
#include "Smedja/Events/ApplicationEvent.h"
#include "Smedja/Events/MouseEvent.h"

#include "EuclideanCamera.h"

namespace Smedja {

class CameraController {
public:
    CameraController(Camera &camera);
    ~CameraController() = default;

    void onEvent(Event &e);

    void onUpdate(TimeStep &deltaTime);

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

    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    // float m_roll;

    // Control variables
    float m_sensitivity = 0.1f;
    float m_moveSpeed = 4.0f;
    float m_mouseXLast = 0.0f;
    float m_mouseYLast = 0.0f;
};

} // namespace Smedja

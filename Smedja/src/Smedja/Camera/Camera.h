#pragma once

#include <glm/glm.hpp>

namespace Smedja {

// Virtual camera class, implementation left up to euclidean/quat camera.
// Camera is responsible for managing and generating the view and projection 
// matracies, nothing else.
// To control the camera and use it, see the CameraController class.
class Camera {
    friend class CameraController;
public:
    Camera() = default;
    Camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up) : 
        m_pos(pos), m_front(front), m_up(up) {}
    ~Camera() = default;

    virtual void updateView() = 0;

    virtual void setPerspective(float fov, float aspect, float near, float far);
    virtual void setOrthographic(float left, float right, float top,
                                 float bottom, float near, float far);

    // getters
    glm::vec3 getPos() const { return m_pos; }
    glm::vec3 getFacing() const { return m_front; }
    // glm::vec3 getRight() const { return m_right; }
    glm::vec3 getUp() const { return m_up; }

    const glm::mat4 &getView() const { return m_view; }
    const glm::mat4 &getProj() const { return m_proj; }
    const glm::mat4 &getProjView() const { return m_projView; }
    // keep adding as necessary

protected:
    glm::vec3 m_pos;
    glm::vec3 m_front;
    // glm::vec3 m_right;
    glm::vec3 m_up;

    glm::mat4 m_view;
    glm::mat4 m_proj;
    glm::mat4 m_projView;

    // projection matrix values
    float m_fovDegree;
    float m_aspectRatio;
    float m_nearPlane;
    float m_farPlane;
    bool m_usePerspective;
};

}


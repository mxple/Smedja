#include "EuclideanCamera.h"
#include "pch.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <glm/gtx/string_cast.hpp>

namespace Smedja {

EuclideanCamera::EuclideanCamera(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
    : Camera(pos, front, up) {
    updateView();
}

void EuclideanCamera::updateView() {
    // Use m_pos + m_front to find center (aka object we are looking at).
    m_view = glm::lookAt(m_pos, m_pos + m_front, m_up);
}

void EuclideanCamera::setPerspective(float fov, float aspect, float near,
                                     float far) {
    m_usePerspective = true;
    m_proj = glm::perspective(fov, aspect, near, far);
    m_fovDegree = fov;
    m_aspectRatio = aspect;
    m_nearPlane = near;
    m_farPlane = far;
}

void EuclideanCamera::setOrthographic(float left, float right, float top,
                                      float bottom, float near, float far) {
    m_usePerspective = false;
    m_proj = glm::ortho(left, right, bottom, top);
    m_nearPlane = near;
    m_farPlane = far;
}

} // namespace Smedja

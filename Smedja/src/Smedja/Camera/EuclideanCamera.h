#pragma once
#include "Camera.h"

namespace Smedja {

class EuclideanCamera : public Camera {
public:
    EuclideanCamera(glm::vec3 pos = {0, 0, 0}, glm::vec3 front = {0, 0, -1}, glm::vec3 up = {0, 1, 0});
    ~EuclideanCamera() = default;

    virtual void updateView() override;

    virtual void setPerspective(float fov, float aspect, float near,
                                float far) override;
    virtual void setOrthographic(float left, float right, float top,
                                 float bottom, float near, float far) override;
};

} // namespace Smedja

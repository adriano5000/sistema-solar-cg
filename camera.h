#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
    Camera() {}
    Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
    {
        perspective = glm::perspective(fov, aspect, zNear, zFar);
        position = pos;
        forward = glm::vec3(0, 0, 1);
        up = glm::vec3(0, 1, 0);
    }

    inline glm::mat4 GetViewProjection() const { return perspective * glm::lookAt(position, position + forward, up); }

    glm::mat4 perspective;
    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up;
};

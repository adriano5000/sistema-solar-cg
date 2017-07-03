#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "camera.h"

class transform
{
public:
    transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
    {
        _position = position;
        _rotation = rotation;
        _scale = scale;
    }

    inline glm::mat4 GetModel() const
    {
        glm::mat4 posMatrix = glm::translate(_position);
        glm::mat4 rotXMatrix = glm::rotate(_rotation.x, glm::vec3(1, 0, 0));
        glm::mat4 rotYMatrix = glm::rotate(_rotation.y, glm::vec3(0, 1, 0));
        glm::mat4 rotZMatrix = glm::rotate(_rotation.z, glm::vec3(0, 0, 1));
        glm::mat4 scaleMatrix = glm::scale(_scale);
        glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;
        return posMatrix * rotMatrix * scaleMatrix;
    }

    inline glm::vec3& GetPosition() { return _position; }
    inline glm::vec3& GetRotation() { return _rotation; }
    inline glm::vec3& GetScale() { return _scale; }

    inline void SetPosition(glm::vec3& position) { _position = position; }
    inline void SetRotation(glm::vec3& rotation) { _rotation = rotation; }
    inline void SetScale(glm::vec3& scale) { _scale = scale; }

    inline glm::mat4 GetModelProjection(const Camera& c) const
    {
        glm::mat4 VP = c.GetViewProjection();
        glm::mat4 M = GetModel();
        return VP * M;
    }

private:
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;
};

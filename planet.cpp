#include "planet.h"

void Planet::Update(double counter, Camera& camera)
{
    _trans.GetPosition().z = (_center.z + _speed.z * cosf(3 * counter));
    _trans.GetPosition().x = (_center.x + _speed.x * sinf(3 * counter));
    _trans.GetPosition().y = _speed.y * cosf(3 * counter);
    _trans.GetRotation().y = 3 * counter;
    _trans.GetScale() = glm::vec3(30, 30, 30);
    _shader->Bind();
    _shader->Update(_trans, camera);
    _texture->Bind(0);
    _mesh->Draw();
}

Planet::Planet(Shader* shader, Texture* texture, Mesh* mesh, const glm::vec3& center, const glm::vec3& scale, const glm::vec3& speed, double rot_speed)
: _shader(shader), _texture(texture), _mesh(mesh), _scale(scale), _speed(speed), _rot_speed(rot_speed), _center(center),
  _trans(center, scale, glm::vec3(0, 0, 0))
{
}
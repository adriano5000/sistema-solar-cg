#include "planet.h"

void Planet::Update(double counter, Camera& camera)
{
    _trans.GetPosition().z = (_center.z + _speed.z * cosf(_rot_speed * counter));
    _trans.GetPosition().x = (_center.x + _speed.x * sinf(_rot_speed * counter));
    _trans.GetPosition().y = _center.y; // + _speed.y * sinf(_rot_speed * counter);
    _trans.GetRotation().y = _rot_speed * counter;
    _trans.GetScale() = _scale;
    _shader->Bind();
    _shader->Update(_trans, camera);
    _texture->Bind(0);
    _mesh->Draw();
}

Planet::Planet(Shader* shader, Texture* texture, Mesh* mesh, const glm::vec3& center, const glm::vec3& scale, const glm::vec3& speed, double rot_speed)
: _shader(shader), _texture(texture), _mesh(mesh), _scale(scale), _speed(speed), _center(center), _rot_speed(rot_speed),
  _trans(center, scale, glm::vec3(0, 0, 0))
{
}
#include "Bullet.hpp"

#include <iostream>

namespace junk {
namespace server {
namespace model {

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

Patch Bullet::getPatch()
{
  Patch patch;
  patch.id = id;

  patch.gameObjectType = GameObjectType::BULLET;
  patch.__set_bulletPatch(getBulletPatch());

  return patch;
}

BulletPatch Bullet::getBulletPatch()
{
  BulletPatch bulletPatch;
  bulletPatch.unitPatch = getUnitPatch();

  /*
    Set fields here
  */

  return bulletPatch;
}

void Bullet::process() {
  GameObject::process();
  // if (lifetime == 100) {
  //   body->GetWorld()->DestroyBody(body);
  // }
  b2Vec2 pos = body->GetWorldCenter();
  position.x = pos.x;
  position.y = pos.y;
}

}}} // namespace junk::server::model

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

}}} // namespace junk::server::model

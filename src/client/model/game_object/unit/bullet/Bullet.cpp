#include "Bullet.hpp"

#include <iostream>

namespace junk {
namespace client {
namespace model {

MODEL_GAME_OBJECT_IMPL(Bullet, bullet, BULLET)

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::applyBulletPatch(const BulletPatch& bulletPatch)
{
  applyUnitPatch(bulletPatch.unitPatch);

  std::cerr << "Bullet.position: " << position.x << " " << position.y << std::endl;
}

}}} // namespace junk::client::model

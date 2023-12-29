#include "Bullet.hpp"

#include "common/logger/Logger.hpp"

namespace junk {
namespace client {
namespace model {

MODEL_GAME_OBJECT_IMPL(Bullet, bullet, BULLET)

Bullet::Bullet() {}

Bullet::~Bullet() {}

void Bullet::applyBulletPatch(const BulletPatch& bulletPatch) {
  applyUnitPatch(bulletPatch.unitPatch);

  type = bulletPatch.type;
  dbg.debug("Bullet.position: ", position.x, " ", position.y);
}

}  // namespace model
}  // namespace client
}  // namespace junk

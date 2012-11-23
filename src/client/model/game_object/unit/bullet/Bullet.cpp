#include "Bullet.hpp"
#include "common/logger/Logger.hpp"

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

  dbg.debug("Bullet.position: ", position.x, " ", position.y);
}

}}} // namespace junk::client::model

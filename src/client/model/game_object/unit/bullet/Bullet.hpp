#pragma once

#include "client/model/game_object/unit/Unit.hpp"
#include "common/game_object/unit/bullet/Bullet.hpp"

namespace junk {
namespace client {
namespace model {

class Bullet : public virtual Unit, public virtual junk::common::Bullet
{
  MODEL_GAME_OBJECT_DEF(Bullet)

public:
  Bullet();
  virtual ~Bullet();

  void applyBulletPatch(const BulletPatch& bulletPatch);

}; // Bullet

}}} // namespace junk::client::model

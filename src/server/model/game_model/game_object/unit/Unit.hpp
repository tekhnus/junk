#pragma once

#include <box2d/box2d.h>

#include "common/game_object/unit/Unit.hpp"
#include "server/model/game_model/game_object/GameObject.hpp"

namespace junk {
namespace server {
namespace model {

class Unit : public virtual GameObject, public virtual junk::common::Unit {
  MODEL_GAME_OBJECT_DEF(Unit)

 public:
  Unit();
  virtual ~Unit();

  UnitPatch getUnitPatch();

  virtual void destroy();
  virtual void startDestruction();

  virtual GameObjectType getType();
  virtual void onBulletHit(int type, const std::string& owner);
  virtual void onBonusEat(int bonusType);

  b2Body* body;

};  // Unit

}  // namespace model
}  // namespace server
}  // namespace junk

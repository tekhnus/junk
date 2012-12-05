#pragma once

#include "server/model/game_model/game_object/GameObject.hpp"
#include "common/game_object/unit/Unit.hpp"

#include <Box2D/Box2D.h>

namespace junk {
namespace server {
namespace model {

class Unit : public virtual GameObject, public virtual junk::common::Unit
{
  MODEL_GAME_OBJECT_DEF(Unit)

public:
  Unit();
  virtual ~Unit();

  UnitPatch getUnitPatch();

  virtual void destroy();
  virtual void startDestruction();

  virtual void onBulletHit();

  b2Body* body;

}; // Unit

}}} // namespace junk::server::model

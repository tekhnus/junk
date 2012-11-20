#pragma once

#include "client/model/game_object/GameObject.hpp"
#include "common/game_object/unit/Unit.hpp"

namespace junk {
namespace client {
namespace model {

class Unit : public virtual GameObject, public virtual junk::common::Unit
{
  MODEL_GAME_OBJECT_DEF(Unit)

public:
  Unit();
  virtual ~Unit();

  void applyUnitPatch(const UnitPatch& unitPatch);

}; // Unit

}}} // namespace junk::client::model

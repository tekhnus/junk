#pragma once

#include "common/game_object/unit/Unit.hpp"
#include "client/model/game_object/unit/Unit.hpp"
#include "client/view/game_object/GameObject.hpp"

namespace junk {
namespace client {
namespace view {

class Unit : public virtual GameObject, public virtual junk::common::Unit
{
  VIEW_GAME_OBJECT_DEF(Unit)

public:
  Unit();
  virtual ~Unit();

  void updateUnit(const model::Unit& unit);

}; // Unit

}}} // namespace junk::client::view

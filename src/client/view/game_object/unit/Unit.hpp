#pragma once

#include "GameObject.hpp"
#include "common/game_object/unit/Unit.hpp"

namespace junk {
namespace client {
namespace view {

class Unit : public virtual GameObject, public virtual junk::common::Unit
{
public:
  Unit();
  virtual ~Unit();

  virtual void update(const model::GameObject& gameObject);

  void updateUnit(const model::Unit& unit);

}; // Unit

}}} // namespace junk::client::view

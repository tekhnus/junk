#pragma once

#include <box2d/box2d.h>

#include "common/game_object/unit/bonus/Bonus.hpp"
#include "server/model/game_model/game_object/unit/Unit.hpp"

namespace junk {
namespace server {
namespace model {

class Bonus : public virtual Unit, public virtual junk::common::Bonus {
  MODEL_GAME_OBJECT_DEF(Bonus)

 public:
  Bonus(b2World *world, sf::Vector2f bornPosition, int bonusType);
  virtual ~Bonus();

  virtual void init();

  BonusPatch getBonusPatch();

  virtual void process();
  virtual void startDestruction();

  virtual GameObjectType getType();

};  // Bonus

}  // namespace model
}  // namespace server
}  // namespace junk

#pragma once

#include "client/model/game_object/unit/bonus/Bonus.hpp"
#include "client/view/game_object/unit/Unit.hpp"
#include "common/game_object/unit/bonus/Bonus.hpp"

namespace junk {
namespace client {
namespace view {

class Bonus : public virtual Unit, public virtual junk::common::Bonus {
  VIEW_GAME_OBJECT_DEF(Bonus)

 public:
  Bonus();
  virtual ~Bonus();

  void updateBonus(const model::Bonus& bonus);

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::CircleShape body;

};  // Bonus

}  // namespace view
}  // namespace client
}  // namespace junk

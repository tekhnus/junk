#pragma once

#include "common/game_object/bonus/Bonus.hpp"
#include "client/model/game_object/bonus/Bonus.hpp"
#include "client/view/game_object/GameObject.hpp"

namespace junk {
namespace client {
namespace view {

class Bonus : public virtual GameObject, public virtual junk::common::Bonus
{
  VIEW_GAME_OBJECT_DEF(Bonus)

public:
  Bonus();
  virtual ~Bonus();

  void updateBonus(const model::Bonus& bonus);

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::CircleShape body;

}; // Bonus

}}} // namespace junk::client::view

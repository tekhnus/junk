#pragma once

#include "client/model/game_object/unit/player/Player.hpp"
#include "client/view/game_object/unit/Unit.hpp"
#include "common/game_object/unit/player/Player.hpp"

namespace junk {
namespace client {
namespace view {

class Player : public virtual Unit, public virtual junk::common::Player {
  VIEW_GAME_OBJECT_DEF(Player)

 public:
  Player();
  virtual ~Player();

  void updatePlayer(const model::Player& player);

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
  sf::CircleShape body, inner;
  sf::RectangleShape gun;
  sf::RectangleShape healthBar, healthBarBackground;
  sf::Text nickname;

};  // Player

}  // namespace view
}  // namespace client
}  // namespace junk

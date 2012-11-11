#pragma once

#include "Unit.hpp"
#include "common/game_object/unit/player/Player.hpp"

namespace junk {
namespace client {
namespace view {

class Player : public virtual Unit, public virtual junk::common::Player
{
  VIEW_GAME_OBJECT_DEF(Player)

public:
  Player();
  virtual ~Player();

  void updatePlayer(const model::Player& player);

}; // Player

}}} // namespace junk::client::view

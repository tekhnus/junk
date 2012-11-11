#pragma once

#include "Unit.hpp"
#include "common/game_object/unit/player/Player.hpp"

namespace junk {
namespace client {
namespace view {

class Player : public virtual Unit, public virtual junk::common::Player
{
public:
  Player();
  virtual ~Player();

  virtual void update(const model::GameObject& gameObject);

  void updatePlayer(const model::Player& player);

}; // Player

}}} // namespace junk::client::view

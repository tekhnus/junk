#pragma once

#include "Unit.hpp"
#include "common/game_object/unit/player/Player.hpp"

namespace junk {
namespace client {
namespace model {

class Player : public virtual Unit, public virtual junk::common::Player
{
  MODEL_GAME_OBJECT_DEF(Player)

public:
  Player();
  virtual ~Player();

  virtual void applyPatch(const Patch& patch);
  void applyPlayerPatch(const PlayerPatch& playerPatch);

}; // Player

}}} // namespace junk::client::model

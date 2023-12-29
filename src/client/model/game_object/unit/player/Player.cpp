#include "Player.hpp"

#include "common/logger/Logger.hpp"

namespace junk {
namespace client {
namespace model {

MODEL_GAME_OBJECT_IMPL(Player, player, PLAYER)

Player::Player() {}

Player::~Player() {}

void Player::applyPlayerPatch(const PlayerPatch& playerPatch) {
  applyUnitPatch(playerPatch.unitPatch);
  setHealth(playerPatch.health);
  setMaxHealth(playerPatch.maxHealth);
  setName(playerPatch.name);
  setScore(playerPatch.score);

  dbg.debug("Player.position: ", position.x, " ", position.y);
}

}  // namespace model
}  // namespace client
}  // namespace junk

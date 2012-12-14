#include "Player.hpp"
#include "common/logger/Logger.hpp"

namespace junk {
namespace client {
namespace model {

MODEL_GAME_OBJECT_IMPL(Player, player, PLAYER)

Player::Player()
{
}

Player::~Player()
{
}

void Player::applyPlayerPatch(const PlayerPatch& playerPatch)
{
  applyUnitPatch(playerPatch.unitPatch);
  setHealth(playerPatch.health);
  setMaxHealth(playerPatch.maxHealth);
  setName(playerPatch.name);

  dbg.debug("Player.position: ", position.x, " ", position.y);
}

}}} // namespace junk::client::model

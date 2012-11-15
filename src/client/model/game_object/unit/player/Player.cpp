#include "Player.hpp"

#include <iostream>

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

  std::cerr << "Player.position: " << position.x << " " << position.y << std::endl;
}

}}} // namespace junk::client::model

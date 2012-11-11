#include "Player.hpp"

namespace junk {
namespace client {
namespace model {

MODEL_GAME_OBJECT_IMPL(Player, player)

Player::Player()
{
}

Player::~Player()
{
}

void Player::applyPlayerPatch(const PlayerPatch& playerPatch)
{
  applyUnitPatch(playerPatch.unitPatch);

  /*
    Apply patch here
  */
}

}}} // namespace junk::client::model

#include "Player.hpp"

namespace junk {
namespace client {
namespace view {

Player::Player()
{
}

Player::~Player()
{
}

void Player::applyPatch(const Patch& patch)
{
  applyPlayerPatch(patch.playerPatch);
}

void Player::applyPlayerPatch(const PlayerPatch& playerPatch)
{
  applyUnitPatch(playerPatch.unitPatch);

  /*
    Apply patch here
  */
}

}}} // namespace junk::client::view

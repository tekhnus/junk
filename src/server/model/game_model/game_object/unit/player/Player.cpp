#include "Player.hpp"

namespace junk {
namespace server {
namespace model {

Player::Player()
{
}

Player::~Player()
{
}

Patch Player::getPatch()
{
  Patch patch;
  patch.id = id;
  patch.gameObjectType = GameObjectType::PLAYER;
  patch.__set_playerPatch(getPlayerPatch());
  return patch;
}

PlayerPatch Player::getPlayerPatch()
{
  PlayerPatch playerPatch;
  playerPatch.unitPatch = getUnitPatch();

  /*
    Set fields here
  */

  return playerPatch;
}

}}} // namespace junk::server::model

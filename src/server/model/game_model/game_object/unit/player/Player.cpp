#include "Player.hpp"

#include <iostream>

namespace junk {
namespace server {
namespace model {

Player::Player()
{
    setMaxHealth(100);
    setHealth(getMaxHealth() - 20);
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
  playerPatch.health = getHealth();
  playerPatch.maxHealth = getMaxHealth();

  /*
    Set fields here
  */

  return playerPatch;
}

void Player::process()
{
  b2Vec2 pos = body->GetWorldCenter();
  double angle = body->GetAngle();
  body->ApplyForceToCenter(force);
  //body->ApplyAngularImpulse(angularImpulse);
  body->ApplyTorque(torque);

  position.x = pos.x;
  position.y = pos.y;

  direction.x = cos(angle);
  direction.y = sin(angle);
}



}}} // namespace junk::server::model

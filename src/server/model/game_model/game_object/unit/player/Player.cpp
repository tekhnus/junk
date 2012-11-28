#include "Player.hpp"

#include <iostream>
#include "common/logger/Logger.hpp"
#include "../bullet/Bullet.hpp"
#include "server/model/game_model/ServerGameModel.hpp"

namespace junk {
namespace server {
namespace model {

Player::Player() : fireOn(false)
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
  GameObject::process();
  b2Vec2 pos = body->GetWorldCenter();
  double angle = body->GetAngle();
  body->ApplyForceToCenter(force);
  //body->ApplyAngularImpulse(angularImpulse);
  body->ApplyTorque(torque);

  position.x = pos.x;
  position.y = pos.y;

  direction.x = cos(angle);
  direction.y = sin(angle);

  processFire();

  if (destroyInfo.isDestroyed)
  {
    destroyInfo.destroyCountdown = std::max(0, destroyInfo.destroyCountdown - 1);
  }

  
}

void Player::processFire()
{
  if(!fireOn ||lifetime % 7 != 0)
    return;
  dbg << "Adding a bullet...";

  Bullet* bullet = new Bullet();

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  dbg.debug("POSITION IS ", position.x, position.y);

  double angle = body->GetAngle();
  double rad = 1.5;
  bodyDef.position.Set(position.x + rad * cos(angle), position.y + rad * sin(angle));
  bodyDef.bullet = true;

  b2Body* bulletBody = body->GetWorld()->CreateBody(&bodyDef);
  dbg << "bullet adding I";

  b2CircleShape circleShape;
  circleShape.m_radius = 1.0f / 7;

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &circleShape;
  fixtureDef.density = 2.0f;
  fixtureDef.restitution = 0.7f;
  dbg << "bullet adding II";

  bulletBody->CreateFixture(&fixtureDef);
  bulletBody->SetLinearDamping(0.1);

  double power = 100;
  bulletBody->ApplyLinearImpulse(b2Vec2(power * cos(angle), power*sin(angle)), bulletBody->GetWorldCenter());

  bullet->body = bulletBody;
  model->addGameObject(bullet);
  dbg << "Bullet added successfully";
}



}}} // namespace junk::server::model

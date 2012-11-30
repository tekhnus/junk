#include "Player.hpp"

#include <iostream>
#include "common/logger/Logger.hpp"
#include "../bullet/Bullet.hpp"
#include "server/model/game_model/ServerGameModel.hpp"

namespace junk {
namespace server {
namespace model {

MODEL_GAME_OBJECT_IMPL(Player, player, PLAYER)

Player::Player() : fireOn(false)
{
    setMaxHealth(100);
    setHealth(getMaxHealth() - 20);
}

Player::~Player()
{
}

PlayerPatch Player::getPlayerPatch()
{
  PlayerPatch playerPatch;
  playerPatch.unitPatch = getUnitPatch();
  playerPatch.health = getHealth();
  playerPatch.maxHealth = getMaxHealth();

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
}

void Player::processFire()
{
  if(!fireOn ||lifetime % 7 != 0)
    return;
  dbg << "Adding a bullet...";

  Bullet* bullet = new Bullet(this);
  model->addGameObject(bullet);
  dbg << "Bullet added successfully";
}

void Player::init()
{
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(3.0f, 3.0f);

  body = model->world->CreateBody(&bodyDef);

  b2CircleShape circleShape;
  circleShape.m_radius = 1.0f;

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &circleShape;
  fixtureDef.density = 1.0f;
  fixtureDef.restitution = 0.5f;

  body->CreateFixture(&fixtureDef);
  body->SetLinearDamping(1.5);
  body->SetUserData((Unit*)this);

  force.SetZero();
  torque = 0.0f;
}

void Player::rotate(const RotateAction& rotateAction)
{
  dbg.debug("Rotate invoked ", rotateAction.direction.x, " ", rotateAction.direction.y);

  sf::Vector2f rotDirection = common::to_SFML_Vector2f(rotateAction.direction);
  rotDirection /= 20.0f;
  rotDirection -= position;

  double DEGTORAD = M_PI / 180;
  double desiredAngle = atan2(rotDirection.y, rotDirection.x);
  double bodyAngle = body->GetAngle();
  float nextAngle = bodyAngle + body->GetAngularVelocity() / 10.0;
  float totalRotation = desiredAngle - nextAngle;

  while ( totalRotation < -180 * DEGTORAD ) totalRotation += 360 * DEGTORAD;
  while ( totalRotation >  180 * DEGTORAD ) totalRotation -= 360 * DEGTORAD;
  float desiredAngularVelocity = totalRotation * 10;
  torque = body->GetInertia() * desiredAngularVelocity / (1/10.0);
<<<<<<< HEAD
}

void Player::move(const MoveAction& moveAction)
{
  dbg << "Move invoked";

  sf::Vector2f moveDirection = common::to_SFML_Vector2f(moveAction.direction);
  moveDirection = 100.0f * moveDirection;

  force.Set(moveDirection.x, moveDirection.y);
}

=======
}

void Player::move(const MoveAction& moveAction)
{
  dbg << "Move invoked";

  sf::Vector2f moveDirection = common::to_SFML_Vector2f(moveAction.direction);
  moveDirection = 100.0f * moveDirection;

  force.Set(moveDirection.x, moveDirection.y);
}

>>>>>>> Removed functionality from SGM
void Player::fire(const FireAction& fireAction)
{
  fireOn = fireAction.on;
}


int Player::getType()
{
  return TYPE_PLAYER;
}

void Player::onBulletHit()
{
  setHealth(getHealth() - getMaxHealth() / 10);
  if (getHealth() <= 0)
  {
    dbg.debug("Low health, killed");
    setHealth(0);
    startDestruction();
  }
}

}}} // namespace junk::server::model

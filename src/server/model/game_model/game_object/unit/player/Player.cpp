#include "Player.hpp"

#include "../bullet/Bullet.hpp"
#include "common/logger/Logger.hpp"
#include "common/utils/Convert.hpp"
#include "server/model/game_model/ServerGameModel.hpp"

namespace junk {
namespace server {
namespace model {

MODEL_GAME_OBJECT_IMPL(Player, player, PLAYER)

Player::Player() : fireOn(false) {
  setMaxHealth(100);
  setHealth(getMaxHealth() - 20);
  forceFactor = 1.0;
  bulletsType = 0;
  setScore(0);
}

Player::~Player() {}

PlayerPatch Player::getPlayerPatch() {
  PlayerPatch playerPatch;
  playerPatch.unitPatch = getUnitPatch();
  playerPatch.health = getHealth();
  playerPatch.maxHealth = getMaxHealth();
  playerPatch.name = getName();

  setScore(model->scoreBoard[getName()]);
  playerPatch.score = getScore();

  return playerPatch;
}

void Player::process() {
  GameObject::process();
  b2Vec2 pos = body->GetWorldCenter();
  double angle = body->GetAngle();
  body->ApplyForceToCenter(force, true);
  body->ApplyTorque(torque, true);

  position.x = pos.x;
  position.y = pos.y;

  direction.x = cos(angle);
  direction.y = sin(angle);

  std::chrono::high_resolution_clock::time_point currentTime =
      std::chrono::high_resolution_clock::now();
  if (forceFactor > 1.0 && slowDownTime <= currentTime) {
    forceFactor = 1.0;
  }

  if (bulletsType > 0 && defaultBulletsTime <= currentTime) {
    bulletsType = 0;
  }

  setChanged();
  processFire();
}

void Player::processFire() {
  if (!fireOn || lifetime % 7 != 0)
    return;
  dbg << "Adding a bullet...";

  Bullet* bullet = new Bullet(this, bulletsType);
  model->addGameObject(bullet);
  dbg << "Bullet added successfully";
}

void Player::init() {
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(3.0f, 3.0f);

  body = model->world->CreateBody(&bodyDef);

  b2CircleShape circleShape;
  circleShape.m_radius = 1.0f;

  auto* fixture = body->CreateFixture(&circleShape, 1.0f);
  fixture->SetRestitution(0.5f);
  body->SetLinearDamping(1.5);
  body->GetUserData().pointer = reinterpret_cast<uintptr_t>((Unit*)this);

  force.SetZero();
  torque = 0.0f;
}

void Player::rotate(const RotateAction& rotateAction) {
  dbg.debug("Rotate invoked ", rotateAction.direction.x, " ",
            rotateAction.direction.y);

  sf::Vector2f rotDirection = common::to_SFML_Vector2f(rotateAction.direction);
  // rotDirection /= 20.0f;
  // rotDirection -= position;

  double DEGTORAD = M_PI / 180;
  double desiredAngle = atan2(rotDirection.y, rotDirection.x);
  double bodyAngle = body->GetAngle();
  float nextAngle = bodyAngle + body->GetAngularVelocity() / 10.0;
  float totalRotation = desiredAngle - nextAngle;

  while (totalRotation < -180 * DEGTORAD) totalRotation += 360 * DEGTORAD;
  while (totalRotation > 180 * DEGTORAD) totalRotation -= 360 * DEGTORAD;
  float desiredAngularVelocity = totalRotation * 10;
  torque = body->GetInertia() * desiredAngularVelocity / (1 / 10.0);
}

void Player::move(const MoveAction& moveAction) {
  dbg << "Move invoked";

  sf::Vector2f moveDirection = common::to_SFML_Vector2f(moveAction.direction);
  moveDirection = 100.0f * moveDirection;

  force.Set(moveDirection.x, moveDirection.y);
  force *= forceFactor;
}

void Player::fire(const FireAction& fireAction) {
  fireOn = fireAction.on;
}

void Player::changeSettings(const ChangeSettingsAction& changeSettingsAction) {
  dbg.debug("Player change setting. Name: ", changeSettingsAction.name);
  setName(changeSettingsAction.name);
}

GameObjectType Player::getType() {
  return GameObjectType::PLAYER;
}

void Player::onBulletHit(int type, const std::string& owner) {
  setHealth(getHealth() - (getMaxHealth() * (1 + type)) / 10);
  if (getHealth() <= 0) {
    model->scoreBoard[getName()]--;
    if (getName() != owner) {
      model->ServerGameModel::scoreBoard[owner]++;
    }

    dbg.debug("Low health, killed");
    setHealth(0);
    startDestruction();
  }
}

void Player::onBonusEat(int bonusType) {
  switch (bonusType) {
    case 0:
      setHealth(std::min(getMaxHealth(), getHealth() + 30));
      break;
    case 1:
      forceFactor = 2.5;
      slowDownTime =
          std::chrono::high_resolution_clock::now() + std::chrono::seconds(5);
      break;
    case 2:
      bulletsType = 1;
      defaultBulletsTime =
          std::chrono::high_resolution_clock::now() + std::chrono::seconds(10);
      break;
    default:
      std::cerr << "Fatal error: Unknown bonus type:" << bonusType << std::endl;
      std::terminate();
  }
  setChanged();
}

bool Player::canSee(GameObject* gameObject) {
  if (gameObject->getType() == GameObjectType::UNIT) {
    Unit* unit = dynamic_cast<Unit*>(gameObject);

    sf::Vector2f distanceVector = unit->position - position;

    double distance = sqrt(distanceVector.x * distanceVector.x +
                           distanceVector.y * distanceVector.y);

    if (distance > 150) {
      return false;
    }
  }
  return true;
}

}  // namespace model
}  // namespace server
}  // namespace junk

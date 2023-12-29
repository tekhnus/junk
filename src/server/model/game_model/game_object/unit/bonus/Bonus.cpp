#include "Bonus.hpp"

namespace junk {
namespace server {
namespace model {

MODEL_GAME_OBJECT_IMPL(Bonus, bonus, BONUS)

Bonus::Bonus(b2World *world, sf::Vector2f bornPosition, int newBonusType) {
  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  // bodyDef.fixedRotation = true;

  bodyDef.position.Set(bornPosition.x, bornPosition.y);

  body = world->CreateBody(&bodyDef);
  body->GetUserData().pointer = reinterpret_cast<uintptr_t>((Unit *)this);

  b2CircleShape circleShape;
  // circleShape.m_p.Set(0.0f, 0.0f);
  circleShape.m_radius = 0.5f;

  // b2FixtureDef fixtureDef;
  // fixtureDef.shape = &circleShape;
  // fixtureDef.density = 2.0f;
  // fixtureDef.restitution = 0.7f;
  // body->CreateFixture(&fixtureDef);
  // This API fails in a very weird way.
  // You may try to uncomment it, but prepare your GDB.
  // Meanwhile, a workaround:
  auto *fixture = body->CreateFixture(&circleShape, 2.0f);
  fixture->SetRestitution(0.7f);
  body->SetLinearDamping(0.1);
  // body->ApplyLinearImpulse(b2Vec2(10, 10), body->GetWorldCenter());

  this->bonusType = newBonusType;
}

Bonus::~Bonus() {}

void Bonus::process() {
  GameObject::process();
  b2Vec2 pos = body->GetWorldCenter();
  if (position.x != pos.x || position.y != pos.y) {
    position.x = pos.x;
    position.y = pos.y;
    setChanged();
  }
}

BonusPatch Bonus::getBonusPatch() {
  BonusPatch bonusPatch;
  bonusPatch.unitPatch = getUnitPatch();

  /*
    Set fields here
  */

  bonusPatch.bonusType = bonusType;

  return bonusPatch;
}

void Bonus::startDestruction() {
  if (!destroyInfo.isDestructing) {
    destroyInfo.isDestructing = true;
    destroyTime = std::chrono::high_resolution_clock::now() +
                  std::chrono::milliseconds(10);
    cleanupTime =
        std::chrono::high_resolution_clock::now() + std::chrono::seconds(10);
  }
  setChanged();
}

GameObjectType Bonus::getType() {
  return GameObjectType::BONUS;
}

void Bonus::init() {}

}  // namespace model
}  // namespace server
}  // namespace junk

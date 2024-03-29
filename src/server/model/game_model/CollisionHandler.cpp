#include "CollisionHandler.hpp"

#include <box2d/b2_contact.h>

#include "server/model/game_model/game_object/unit/Unit.hpp"
#include "server/model/game_model/game_object/unit/bonus/Bonus.hpp"
#include "server/model/game_model/game_object/unit/bullet/Bullet.hpp"

namespace junk {
namespace server {
namespace model {

void CollisionHandler::BeginContact(b2Contact* contact) {
  b2Fixture* aF = contact->GetFixtureA();
  b2Fixture* bF = contact->GetFixtureB();
  b2Body* a = aF->GetBody();
  b2Body* b = bF->GetBody();
  uintptr_t aRaw = a->GetUserData().pointer;
  uintptr_t bRaw = b->GetUserData().pointer;
  if (aRaw == 0 || bRaw == 0) {
    return;
  }
  Unit* aUnit = reinterpret_cast<Unit*>(aRaw);
  Unit* bUnit = reinterpret_cast<Unit*>(bRaw);

  if ((aUnit->getType() == GameObjectType::PLAYER &&
       bUnit->getType() == GameObjectType::BONUS) ||
      (aUnit->getType() == GameObjectType::BONUS &&
       bUnit->getType() == GameObjectType::PLAYER)) {
    Unit* uPlayer = aUnit;
    Unit* uBonus = bUnit;
    if (aUnit->getType() == GameObjectType::BONUS &&
        bUnit->getType() == GameObjectType::PLAYER) {
      std::swap(uPlayer, uBonus);
    }

    uPlayer->onBonusEat(dynamic_cast<Bonus*>(uBonus)->bonusType);
    uBonus->startDestruction();
  }

  if (bUnit->getType() == GameObjectType::PLAYER &&
      aUnit->getType() == GameObjectType::BULLET) {
    bUnit->onBulletHit(dynamic_cast<Bullet*>(aUnit)->type,
                       dynamic_cast<Bullet*>(aUnit)->getOwner());
  }
  if (aUnit->getType() == GameObjectType::PLAYER &&
      bUnit->getType() == GameObjectType::BULLET) {
    aUnit->onBulletHit(dynamic_cast<Bullet*>(bUnit)->type,
                       dynamic_cast<Bullet*>(bUnit)->getOwner());
  }
  if (aUnit->getType() == GameObjectType::PLAYER &&
      bUnit->getType() == GameObjectType::BULLET) {
    bUnit->startDestruction();
  }
  if (bUnit->getType() == GameObjectType::PLAYER &&
      aUnit->getType() == GameObjectType::BULLET) {
    aUnit->startDestruction();
  }
}

}  // namespace model
}  // namespace server
}  // namespace junk

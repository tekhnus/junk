#include "CollisionHandler.hpp"
#include "common/logger/Logger.hpp"
#include <typeinfo>

namespace junk {
namespace server {
namespace model {

void CollisionHandler::BeginContact(b2Contact* contact)
{
  b2Fixture* aF = contact->GetFixtureA();
  b2Fixture* bF = contact->GetFixtureB();
  b2Body* a = aF->GetBody();
  b2Body* b = bF->GetBody();
  void* aRaw = a->GetUserData();
  void* bRaw = b->GetUserData();
  if (aRaw == NULL || bRaw == NULL)
  {
    return;
  }
  Unit* aUnit = (Unit*)aRaw;
  Unit* bUnit = (Unit*)bRaw;

  if (
          (aUnit->getType() == TYPE_PLAYER && bUnit->getType() == TYPE_BONUS) ||
          (aUnit->getType() == TYPE_BONUS && bUnit->getType() == TYPE_PLAYER)
         )
  {
      Unit *uPlayer = aUnit, *uBonus = bUnit;
      if (aUnit->getType() == TYPE_BONUS && bUnit->getType() == TYPE_PLAYER)
      {
          std::swap(uPlayer, uBonus);
      }

      uPlayer->onBonusEat(dynamic_cast<Bonus*>(uBonus)->bonusType);
      uBonus->startDestruction();
  }

  if (bUnit->getType() == TYPE_PLAYER && aUnit->getType() == TYPE_BULLET)
  {
    bUnit->onBulletHit(dynamic_cast<Bullet*>(aUnit)->type);
  }
  if (aUnit->getType() == TYPE_PLAYER && bUnit->getType() == TYPE_BULLET)
  {
    aUnit->onBulletHit(dynamic_cast<Bullet*>(bUnit)->type);
  }
  if (aUnit->getType() == TYPE_PLAYER && bUnit->getType() == TYPE_BULLET)
  {
    bUnit->startDestruction();
  }
  if (bUnit->getType() == TYPE_PLAYER && aUnit->getType() == TYPE_BULLET)
  {
    aUnit->startDestruction();
  }
}

}}} // namespace junk::server::model

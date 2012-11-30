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
  if (aRaw == nullptr || bRaw == nullptr)
  {
    return;
  }
  Unit* aUnit = (Unit*) (aRaw);
  Unit* bUnit = (Unit*) (bRaw);
  if (aUnit->getType() == TYPE_BULLET)
  {
    bUnit->onBulletHit();
    aUnit->startDestruction();
  }
  if (bUnit->getType() == TYPE_BULLET)
  {
    aUnit->onBulletHit();
    bUnit->startDestruction();
  }
}

}}} // namespace junk::server::model

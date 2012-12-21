#include "Unit.hpp"
#include "common/utils/Convert.hpp"

#include <iostream>

namespace junk {
namespace server {
namespace model {

MODEL_GAME_OBJECT_IMPL(Unit, unit, UNIT)

Unit::Unit()
{
}

Unit::~Unit()
{
}

UnitPatch Unit::getUnitPatch()
{
  UnitPatch unitPatch;
  unitPatch.gameObjectPatch = getGameObjectPatch();

  unitPatch.position = common::to_thrift_Vector2f(position);
  unitPatch.direction = common::to_thrift_Vector2f(direction);

  return unitPatch;
}

void Unit::destroy()
{
  if (!isRemoved)
  {
    b2World* world = body->GetWorld();
    world->DestroyBody(body);
    isRemoved = true;
  }
}

void Unit::startDestruction()
{
  if (!destroyInfo.isDestructing)
  {
    destroyInfo.isDestructing = true;
    destroyTime = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(100);
    cleanupTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(10);
    setChanged();
  }
}

GameObjectType Unit::getType()
{
  return GameObjectType::UNIT;
}

void Unit::onBulletHit(int type)
{}

void Unit::onBonusEat(int bonusType)
{}

}}} // namespace junk::server::model

#include "Unit.hpp"
#include "common/utils/Convert.hpp"

#include <iostream>

namespace junk {
namespace server {
namespace model {

Unit::Unit()
{
}

Unit::~Unit()
{
}

Patch Unit::getPatch()
{
  Patch patch;
  patch.id = id;
  patch.gameObjectType = GameObjectType::UNIT;
  patch.unitPatch = getUnitPatch();
  return patch;
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
  body->GetWorld()->DestroyBody(body);
}

void Unit::startDestruction()
{
  destroyInfo.isDestroyed = true;
  destroyInfo.destroyCountdown = 10;
}

void Unit::onBulletHit()
{}

}}} // namespace junk::server::model

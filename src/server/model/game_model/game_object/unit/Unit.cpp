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

void Unit::process()
{
  b2Vec2 pos = body->GetWorldCenter();
  body->ApplyForceToCenter(force);
//  body->Dump();
  position.x = pos.x;
  position.y = pos.y;
}

}}} // namespace junk::server::model

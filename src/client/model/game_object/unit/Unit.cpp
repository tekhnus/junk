#include "Unit.hpp"

#include <iostream>

namespace junk {
namespace client {
namespace model {

MODEL_GAME_OBJECT_IMPL(Unit, unit, UNIT)

Unit::Unit()
{
}

Unit::~Unit()
{
}

void Unit::applyUnitPatch(const UnitPatch& unitPatch)
{
  applyGameObjectPatch(unitPatch.gameObjectPatch);

  position = common::to_SFML_Vector2f(unitPatch.position);
  direction = common::to_SFML_Vector2f(unitPatch.direction);

  std::cerr << "Applying UnitPatch" << std::endl;
  std::cerr << position.x << " " << position.y << std::endl;
}

}}} // namespace junk::client::model

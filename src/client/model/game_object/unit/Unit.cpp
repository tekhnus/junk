#include "Unit.hpp"
#include "common/logger/Logger.hpp"
#include "common/utils/Convert.hpp"

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

  dbg << "Applying UnitPatch";
  dbg.debug(position.x, " ", position.y);
}

}}} // namespace junk::client::model

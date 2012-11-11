#include "Unit.hpp"

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
  /*
    Apply patch here
  */
}

}}} // namespace junk::client::model

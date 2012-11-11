#include "Unit.hpp"

namespace junk {
namespace client {
namespace model {

Unit::Unit()
{
}

Unit::~Unit()
{
}

void Unit::applyPatch(const Patch& patch)
{
  applyUnitPatch(patch.unitPatch);
  updateSignal(this);
}

void Unit::applyUnitPatch(const UnitPatch& unitPatch)
{
  applyGameObjectPatch(unitPatch.gameObjectPatch);
  /*
    Apply patch here
  */
}

}}} // namespace junk::client::model

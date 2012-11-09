#include "Unit.hpp"

namespace junk {
namespace client {
namespace view {

Unit::Unit()
{
}

Unit::~Unit()
{
}

void Unit::applyPatch(const Patch& patch)
{
  applyUnitPatch(patch.unitPatch);
}

void Unit::applyUnitPatch(const UnitPatch& unitPatch)
{
  applyGameObjectPatch(unitPatch.gameObjectPatch);
  /*
    Apply patch here
  */
}

}}} // namespace junk::client::view

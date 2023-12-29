#include "Unit.hpp"

namespace junk {
namespace client {
namespace view {

VIEW_GAME_OBJECT_IMPL(Unit, unit, UNIT)

Unit::Unit() {}

Unit::~Unit() {}

void Unit::updateUnit(const model::Unit&) {}

}  // namespace view
}  // namespace client
}  // namespace junk

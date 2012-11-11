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

Unit::update(const model::GameObject& gameObject)
{
  updateUnit(reinterpret_cast<const model::Unit&> gameObject);
}

void Unit::updateUnit(const model::Unit& unit)
{
}

}}} // namespace junk::client::view

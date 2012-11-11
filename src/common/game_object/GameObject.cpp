#include "GameObject.hpp"

namespace junk {
namespace common {

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

int32_t GameObject::getId() const
{
  return id;
}

}} // namespace junk::common

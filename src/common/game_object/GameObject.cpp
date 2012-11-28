#include "GameObject.hpp"

namespace junk {
namespace common {

GameObject::GameObject()
{
  destroyInfo.isDestroyed = false;
  destroyInfo.destroyCountdown = 0;
}

GameObject::~GameObject()
{
}

}} // namespace junk::common

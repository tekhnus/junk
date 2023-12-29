#include "GameObject.hpp"

namespace junk {
namespace common {

GameObject::GameObject() {
  destroyInfo.isDestructing = false;
  destroyInfo.destroyCountdown = 0;
}

GameObject::~GameObject() {}

bool GameObject::isDestroyed() const {
  return destroyInfo.isDestructing && (destroyInfo.destroyCountdown == 0);
}

}  // namespace common
}  // namespace junk

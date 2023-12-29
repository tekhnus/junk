#include "GameObject.hpp"

#include "common/logger/Logger.hpp"

namespace junk {
namespace client {
namespace model {

MODEL_GAME_OBJECT_IMPL(GameObject, gameObject, GAME_OBJECT)

GameObject::GameObject() {}

GameObject::~GameObject() {}

void GameObject::applyGameObjectPatch(const GameObjectPatch &gameObjectPatch) {
  destroyInfo.isDestructing = gameObjectPatch.destroyInfo.isDestructing;
  if (gameObjectPatch.destroyInfo.isDestructing) {
    dbg << "Object destroyed " + std::to_string(id);

    destroyInfo.destroyCountdown = gameObjectPatch.destroyInfo.destroyCountdown;
  }
}

}  // namespace model
}  // namespace client
}  // namespace junk

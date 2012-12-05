#include "GameObject.hpp"
#include "common/logger/Logger.hpp"

namespace junk {
namespace client {
namespace model {

MODEL_GAME_OBJECT_IMPL(GameObject, gameObject, GAME_OBJECT)

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::applyGameObjectPatch(const GameObjectPatch &gameObjectPatch)
{
  destroyInfo.isDestroyed = gameObjectPatch.destroyInfo.isDestroyed;
  if (gameObjectPatch.destroyInfo.isDestroyed)
  {
    dbg << "Object destroyed " + std::to_string(id);

    destroyInfo.destroyCountdown = gameObjectPatch.destroyInfo.destroyCountdown;
  }
}

}}} // namespace junk::client::model

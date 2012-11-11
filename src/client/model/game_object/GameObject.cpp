#include "GameObject.hpp"

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
  /*
    Apply patch here
  */
}

}}} // namespace junk::client::model

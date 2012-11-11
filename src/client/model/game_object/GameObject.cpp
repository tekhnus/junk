#include "GameObject.hpp"

namespace junk {
namespace client {
namespace model {

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::applyPatch(const Patch &patch)
{
  applyGameObjectPatch(patch.gameObjectPatch);
  updateSignal(this);
}

void GameObject::applyGameObjectPatch(const GameObjectPatch &gameObjectPatch)
{
  /*
    Apply patch here
  */
}

} // namespace junk::client::model

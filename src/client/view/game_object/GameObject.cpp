#include "GameObject.hpp"

namespace junk {
namespace client {
namespace view {

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

Patch GameObject::applyPatch(const Patch &patch)
{
  patch.gameObjectPatch = applyGameObjectPatch(patch.gameObjectPatch);
}

void GameObject::applyGameObjectPatch(const GameObjectPatch &gameObjectPatch)
{
  /*
    Apply patch here
  */
}

} // namespace junk::client::view

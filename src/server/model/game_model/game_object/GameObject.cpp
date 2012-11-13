#include "GameObject.hpp"

namespace junk {
namespace server {
namespace model {

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

Patch GameObject::getPatch()
{
  Patch patch;
  patch.gameObjectPatch = getGameObjectPatch();
  return patch;
}

GameObjectPatch GameObject::getGameObjectPatch()
{
  GameObjectPatch gameObjectPatch;

  /*
    Set fields here
  */

  return gameObjectPatch;
}

}}} // namespace junk::server::model

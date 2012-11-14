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
  patch.id = id;
  patch.gameObjectType = GameObjectType::GAME_OBJECT;
  patch.gameObjectPatch = getGameObjectPatch();
  return patch;
}

GameObjectPatch GameObject::getGameObjectPatch()
{
  GameObjectPatch gameObjectPatch;

  gameObjectPatch.id = id;

  return gameObjectPatch;
}

}}} // namespace junk::server::model

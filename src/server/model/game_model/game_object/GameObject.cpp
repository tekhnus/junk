#include "GameObject.hpp"

namespace junk {
namespace server {
namespace model {

GameObject::GameObject() : lifetime(0)
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

void GameObject::process()
{
    ++lifetime;
}

}}} // namespace junk::server::model

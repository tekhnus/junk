#include "GameObject.hpp"

namespace junk {
namespace server {
namespace model {

int TYPE_PLAYER = 1;
int TYPE_BULLET = 2;
int TYPE_BONUS = 3;

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
  gameObjectPatch.destroyInfo.isDestroyed = destroyInfo.isDestroyed;
  if (destroyInfo.isDestroyed)
  {
    gameObjectPatch.destroyInfo.destroyCountdown = destroyInfo.destroyCountdown;
  }

  return gameObjectPatch;
}

void GameObject::process()
{
    ++lifetime;
}

}}} // namespace junk::server::model

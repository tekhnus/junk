#include "GameObject.hpp"

namespace junk {
namespace server {
namespace model {

int TYPE_PLAYER = 1;
int TYPE_BULLET = 2;

MODEL_GAME_OBJECT_IMPL(GameObject, gameObject, GAME_OBJECT)

GameObject::GameObject() : lifetime(0)
{
}

GameObject::~GameObject()
{
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
    if (destroyInfo.isDestroyed)
    {
      destroyInfo.destroyCountdown = std::max(0, destroyInfo.destroyCountdown - 1);
    }
}

}}} // namespace junk::server::model

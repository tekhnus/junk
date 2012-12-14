#include "GameObject.hpp"

namespace junk {
namespace server {
namespace model {

int TYPE_PLAYER = 1;
int TYPE_BULLET = 2;
int TYPE_WALL = 3;
int TYPE_BONUS = 4;

MODEL_GAME_OBJECT_IMPL(GameObject, gameObject, GAME_OBJECT)

GameObject::GameObject() : lifetime(0), isRemoved(0)
{
  setChanged();
}

GameObject::~GameObject()
{
}

void GameObject::setChanged()
{
  lastUpdateTime = std::chrono::high_resolution_clock::now();
}

GameObjectPatch GameObject::getGameObjectPatch()
{
  GameObjectPatch gameObjectPatch;

  gameObjectPatch.id = id;
  gameObjectPatch.destroyInfo.isDestructing = destroyInfo.isDestructing;
  if (destroyInfo.isDestructing)
  {
    gameObjectPatch.destroyInfo.destroyCountdown = destroyInfo.destroyCountdown;
  }

  return gameObjectPatch;
}

void GameObject::process()
{
    ++lifetime;
    if (destroyInfo.isDestructing)
    {
      destroyInfo.destroyCountdown = (destroyTime - std::chrono::high_resolution_clock::now()).count();
      setChanged();
    }
}

void GameObject::startDestruction()
{
  if (!destroyInfo.isDestructing)
  {
    destroyInfo.isDestructing = true;
    destroyTime = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(100);
    cleanupTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(10);
  }
  setChanged();
}

}}} // namespace junk::server::model

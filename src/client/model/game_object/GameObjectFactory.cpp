#include "GameObjectFactory.hpp"

namespace junk {
namespace client {
namespace model {

GameObjectFactory::GameObjectFactory()
{
}

//std::unordered_map<int, std::function<GameObject* ()> > GameObjectFactory::gameObjectCreator;

GameObject* GameObjectFactory::create(const GameObjectType::type &gameObjectType)
{
  return gameObjectCreator[gameObjectType]();
}

void GameObjectFactory::registerCreator(GameObjectType gameObjectType, std::function<GameObject *()> creator)
{
  gameObjectCreator[gameObjectType] = creator;
}

}}} // namespace junk::client::model

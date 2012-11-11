#include "GameObjectFactory.hpp"

namespace junk {
namespace client {
namespace view {

GameObjectFactory::GameObjectFactory()
{
}

std::unordered_map<int, std::function<GameObject* ()> > GameObjectFactory::gameObjectCreator;

GameObject* GameObjectFactory::create(const GameObjectType::type& gameObjectType)
{
  return gameObjectCreator[gameObjectType]();
}

bool GameObjectFactory::registerCreator(GameObjectType::type gameObjectType,
                                        std::function<GameObject *()> creator)
{
  gameObjectCreator[gameObjectType] = creator;
  return true;
}

}}} // namespace junk::client::view

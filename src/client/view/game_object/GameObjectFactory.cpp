#include "GameObjectFactory.hpp"

namespace junk {
namespace client {
namespace view {

GameObjectFactory::GameObjectFactory()
{
}

GameObject* GameObjectFactory::create(const GameObjectType::type& gameObjectType)
{
  return gameObjectCreator[gameObjectType]();
}

void GameObjectFactory::registerCreator(GameObjectType::type gameObjectType,
                                        std::function<GameObject *()> creator)
{
  gameObjectCreator[gameObjectType] = creator;
}

}}} // namespace junk::client::view

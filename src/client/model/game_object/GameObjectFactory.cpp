#include "GameObjectFactory.hpp"

#include <iostream>

namespace junk {
namespace client {
namespace model {

GameObjectFactory::GameObjectFactory() : logger("CLIENT_GAME_OBJECT_FACTORY", "client_model.log", true)
{
  logger << "GameObjectFactory created";
}

GameObjectFactory::~GameObjectFactory()
{
  logger << "GameObjectFactory destructed";
}

std::unordered_map<int, std::function<GameObject* ()> > GameObjectFactory::gameObjectCreator;

GameObject* GameObjectFactory::create(const GameObjectType::type &gameObjectType)
{
  logger << "Creating new object of type " + std::to_string(gameObjectType);
  return gameObjectCreator[gameObjectType]();
}

bool GameObjectFactory::registerCreator(GameObjectType::type gameObjectType,
                                        std::function<GameObject *()> creator)
{
  //cerr
  std::cerr << "Registring new creator of type " + std::to_string(gameObjectType) << std::endl;
  gameObjectCreator[gameObjectType] = creator;
  return true;
}

}}} // namespace junk::client::model

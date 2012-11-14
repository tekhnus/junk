#pragma once

#include <gen-cpp/Patches_types.h>
#include "GameObject.hpp"
#include "common/logger/Logger.hpp"

#include <unordered_map>

namespace junk {
namespace client {
namespace model {

class GameObject;

class GameObjectFactory
{
public:
  GameObjectFactory();

  ~GameObjectFactory();

  GameObject* create(const GameObjectType::type& gameObjectType);
  static bool registerCreator(GameObjectType::type gameObjectType, std::function<GameObject* (void)> creator);

private:

  static std::unordered_map<int, std::function<GameObject* ()> > gameObjectCreator;
  Logger logger;
};

}}} // namespace junk::client::model

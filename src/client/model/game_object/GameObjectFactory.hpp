#pragma once

#include <gen-cpp/Patches_types.h>
#include "GameObject.hpp"

#include <unordered_map>

namespace junk {
namespace client {
namespace model {

class GameObject;

class GameObjectFactory
{
public:
  GameObjectFactory();

  GameObject* create(const GameObjectType::type& gameObjectType);
  static bool registerCreator(GameObjectType::type gameObjectType, std::function<GameObject* (void)> creator);

private:

  static std::unordered_map<int, std::function<GameObject* ()> > gameObjectCreator;
};

}}} // namespace junk::client::model

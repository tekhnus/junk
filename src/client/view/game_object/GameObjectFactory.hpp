#pragma once

#include <gen-cpp/Patches_types.h>

#include <unordered_map>

#include "GameObject.hpp"
#include "common/logger/Logger.hpp"

namespace junk {
namespace client {
namespace view {

class GameObject;

class GameObjectFactory {
 public:
  GameObjectFactory();
  ~GameObjectFactory();

  GameObject* create(const GameObjectType::type& gameObjectType);

  template <class T>
  static bool registerCreator(GameObjectType::type gameObjectType) {
    logger << "Registring new creator of type " +
                  std::to_string(gameObjectType);
    gameObjectCreator[gameObjectType] =
        std::function<GameObject*()>([&] { return new T(); });
    return true;
  }

 private:
  static std::unordered_map<int, std::function<GameObject*()> >
      gameObjectCreator;
  static Logger logger;
};

}  // namespace view
}  // namespace client
}  // namespace junk

#pragma once

#include <chrono>

#include "common/game_object/GameObject.hpp"
#include "gen-cpp/Patches_types.h"

#define MODEL_GAME_OBJECT_DEF(_name) \
 public:                             \
  virtual Patch getPatch();

#define MODEL_GAME_OBJECT_IMPL(_Name, _name, _NAME)     \
  Patch _Name::getPatch() {                             \
    Patch patch;                                        \
    patch.id = id;                                      \
    patch.gameObjectType = junk::GameObjectType::_NAME; \
    patch.isCleanedUp = isRemoved;                      \
    patch.__set_##_name##Patch(get##_Name##Patch());    \
    return patch;                                       \
  }

namespace junk {
namespace server {
namespace model {

enum class GameObjectType {
  GAME_OBJECT = 0,
  UNIT = 1,
  PLAYER = 2,
  BULLET = 3,
  WALL = 4,
  BONUS = 5
};

class ServerGameModel;

class GameObject : public virtual junk::common::GameObject {
  MODEL_GAME_OBJECT_DEF(GameObject)

 public:
  GameObject();
  virtual ~GameObject();

  virtual void init() = 0;

  virtual void setChanged();

  virtual void process();
  virtual void destroy() = 0;
  virtual void startDestruction();
  GameObjectPatch getGameObjectPatch();

  virtual GameObjectType getType() = 0;

  ServerGameModel* model;
  int lifetime;
  std::chrono::high_resolution_clock::time_point cleanupTime;
  std::chrono::high_resolution_clock::time_point destroyTime;
  std::chrono::high_resolution_clock::time_point lastUpdateTime;

  bool isRemoved;

};  // GameObject

}  // namespace model
}  // namespace server
}  // namespace junk

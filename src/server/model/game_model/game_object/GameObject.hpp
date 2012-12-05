#pragma once

#include "common/game_object/GameObject.hpp"
#include "gen-cpp/Patches_types.h"

#include <chrono>

#define MODEL_GAME_OBJECT_DEF( _name ) \
public: virtual Patch getPatch();

#define MODEL_GAME_OBJECT_IMPL( _Name, _name, _NAME) \
Patch _Name::getPatch() \
{ \
  Patch patch; \
  patch.id = id; \
  patch.gameObjectType = GameObjectType::_NAME; \
  patch.isCleanedUp = destroyInfo.isDestroyed && (destroyInfo.destroyCountdown == 0); \
  patch.__set_ ##_name## Patch(get ##_Name## Patch()); \
  return patch; \
}

namespace junk {
namespace server {
namespace model {

extern int TYPE_PLAYER;
extern int TYPE_BULLET;

class ServerGameModel;

class GameObject : public virtual junk::common::GameObject
{
  MODEL_GAME_OBJECT_DEF(GameObject)

public:
  GameObject();
  virtual ~GameObject();

  virtual void init() = 0;

  GameObjectPatch getGameObjectPatch();

  virtual void process();
  virtual void destroy() = 0;
  virtual void startDestruction() = 0;

  virtual int getType() = 0;

  ServerGameModel* model;
  int lifetime;
  std::chrono::high_resolution_clock::time_point cleanupTime;

}; // GameObject

}}} // namespace junk::client::model

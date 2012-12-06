#pragma once

#include "server/model/game_model/game_object/GameObject.hpp"
#include "common/game_object/wall/Wall.hpp"

#include <Box2D/Box2D.h>

namespace junk {
namespace server {
namespace model {

class Wall : public virtual GameObject, public virtual junk::common::Wall
{
  MODEL_GAME_OBJECT_DEF(Wall)

public:
  Wall();
  virtual ~Wall();

  WallPatch getWallPatch();

  virtual void destroy();
  virtual void startDestruction();

  virtual void onBulletHit();

}; // Wall

}}} // namespace junk::server::model

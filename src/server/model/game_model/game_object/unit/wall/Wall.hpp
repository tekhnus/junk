#pragma once

#include "server/model/game_model/game_object/unit/Unit.hpp"
#include "common/game_object/unit/wall/Wall.hpp"

#include <box2d/box2d.h>

namespace junk {
namespace server {
namespace model {

class Wall : public virtual Unit, public virtual junk::common::Wall
{
  MODEL_GAME_OBJECT_DEF(Wall)

public:
  Wall();
  virtual ~Wall();

  WallPatch getWallPatch();

  virtual void destroy();

  virtual void onBulletHit(int type, const std::string& owner);

  virtual void init();
  virtual GameObjectType getType();
  void setCorners(const std::vector<b2Vec2>& corners);

  b2Body* body;
private:
  std::vector<b2Vec2> corns;

}; // Wall

}}} // namespace junk::server::model

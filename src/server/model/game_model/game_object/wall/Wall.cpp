#include "Wall.hpp"
#include "common/utils/Convert.hpp"

#include <iostream>

namespace junk {
namespace server {
namespace model {

MODEL_GAME_OBJECT_IMPL(Wall, wall, WALL)

Wall::Wall()
{
}

Wall::~Wall()
{
}

WallPatch Wall::getWallPatch()
{
  WallPatch wallPatch;
  wallPatch.gameObjectPatch = getGameObjectPatch();
  // some code here
  return wallPatch;
}

void Wall::destroy()
{
  if (!isRemoved)
  {
    // some code here
    isRemoved = true;
  }
}

void Wall::onBulletHit()
{}

}}} // namespace junk::server::model

#include "Wall.hpp"
#include "common/logger/Logger.hpp"

namespace junk {
namespace client {
namespace model {

MODEL_GAME_OBJECT_IMPL(Wall, wall, WALL)

Wall::Wall()
{
}

Wall::~Wall()
{
}

void Wall::applyWallPatch(const WallPatch& wallPatch)
{
  applyGameObjectPatch(wallPatch.gameObjectPatch);
  // apply what you need
}

}}} // namespace junk::client::model

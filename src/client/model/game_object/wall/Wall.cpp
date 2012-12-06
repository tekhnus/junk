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
  corners.clear();
  for (const auto& corner : wallPatch.corners)
  {
    corners.push_back(junk::common::to_SFML_Vector2f(corner));
  }
}

}}} // namespace junk::client::model

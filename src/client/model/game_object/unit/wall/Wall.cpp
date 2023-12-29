#include "Wall.hpp"

#include "common/logger/Logger.hpp"
#include "common/utils/Convert.hpp"

namespace junk {
namespace client {
namespace model {

MODEL_GAME_OBJECT_IMPL(Wall, wall, WALL)

Wall::Wall() {}

Wall::~Wall() {}

void Wall::applyWallPatch(const WallPatch& wallPatch) {
  applyUnitPatch(wallPatch.unitPatch);
  dbg.debug("Applying wall patch, ", wallPatch.corners.size(), " corners");
  corners.clear();
  for (const auto& corner : wallPatch.corners) {
    corners.push_back(junk::common::to_SFML_Vector2f(corner));
  }
}

}  // namespace model
}  // namespace client
}  // namespace junk

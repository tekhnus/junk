#pragma once

#include "client/model/game_object/unit/Unit.hpp"
#include "common/game_object/unit/wall/Wall.hpp"

namespace junk {
namespace client {
namespace model {

class Wall : public virtual Unit, public virtual junk::common::Wall {
  MODEL_GAME_OBJECT_DEF(Wall)

 public:
  Wall();
  virtual ~Wall();

  void applyWallPatch(const WallPatch& wallPatch);

  std::vector<sf::Vector2f> corners;

};  // Wall

}  // namespace model
}  // namespace client
}  // namespace junk

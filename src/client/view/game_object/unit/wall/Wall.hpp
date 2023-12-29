#pragma once

#include "client/model/game_object/unit/wall/Wall.hpp"
#include "client/view/game_object/unit/Unit.hpp"
#include "common/game_object/unit/wall/Wall.hpp"

namespace junk {
namespace client {
namespace view {

class Wall : public virtual Unit, public virtual junk::common::Wall {
  VIEW_GAME_OBJECT_DEF(Wall)

 public:
  Wall();
  virtual ~Wall();

  void updateWall(const model::Wall& wall);
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
  sf::ConvexShape body;

};  // Wall

}  // namespace view
}  // namespace client
}  // namespace junk

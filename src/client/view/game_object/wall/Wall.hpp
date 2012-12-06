#pragma once

#include "common/game_object/wall/Wall.hpp"
#include "client/model/game_object/wall/Wall.hpp"
#include "client/view/game_object/GameObject.hpp"

namespace junk {
namespace client {
namespace view {

class Wall : public virtual GameObject, public virtual junk::common::Wall
{
  VIEW_GAME_OBJECT_DEF(Wall)

public:
  Wall();
  virtual ~Wall();

  void updateWall(const model::Wall& wall);

}; // Wall

}}} // namespace junk::client::view

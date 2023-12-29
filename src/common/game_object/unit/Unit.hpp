#pragma once

#include "common/game_object/GameObject.hpp"

namespace junk {
namespace common {

class Unit : public virtual GameObject {
 public:
  Unit();
  virtual ~Unit();

  sf::Vector2f position;
  sf::Vector2f direction;
};

}  // namespace common
}  // namespace junk

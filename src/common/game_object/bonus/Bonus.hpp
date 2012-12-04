#pragma once

#include "common/game_object/GameObject.hpp"

namespace junk {
namespace common {

class Bonus : public virtual GameObject
{
public:
  Bonus();
  virtual ~Bonus();

  sf::Vector2f position;
}; // Bonus

}} // namespace junk::common

#pragma once

#include "common/game_object/unit/Unit.hpp"

namespace junk {
namespace common {

class Player : public virtual Unit
{
public:
  Player();
  virtual ~Player();

  int32_t getHealth() const;
  int32_t getMaxHealth() const;
  void setHealth(int32_t health);
  void setMaxHealth(int32_t maxHealth);

private:
  int32_t health, maxHealth;
};

}} // namespace junk::common

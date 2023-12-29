#pragma once

#include "common/game_object/unit/Unit.hpp"

namespace junk {
namespace common {

class Player : public virtual Unit {
 public:
  Player();
  virtual ~Player();

  int32_t getHealth() const;
  int32_t getMaxHealth() const;
  const std::string& getName() const;
  int getScore() const;

  void setHealth(int32_t health);
  void setMaxHealth(int32_t maxHealth);
  void setName(const std::string& name);
  void setScore(int score);

 private:
  int32_t health, maxHealth, score;
  std::string name;
};

}  // namespace common
}  // namespace junk

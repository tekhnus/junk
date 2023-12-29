#pragma once

#include "common/game_object/unit/Unit.hpp"

namespace junk {
namespace common {

class Bonus : public virtual Unit {
 public:
  Bonus();
  virtual ~Bonus();

  int32_t bonusType;
};  // Bonus

}  // namespace common
}  // namespace junk

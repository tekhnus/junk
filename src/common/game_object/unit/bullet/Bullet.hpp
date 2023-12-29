#pragma once

#include "common/game_object/unit/Unit.hpp"

namespace junk {
namespace common {

class Bullet : public virtual Unit {
 public:
  Bullet();
  virtual ~Bullet();

  int type;
};

}  // namespace common
}  // namespace junk

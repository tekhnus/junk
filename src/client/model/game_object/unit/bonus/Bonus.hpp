#pragma once

#include "client/model/game_object/unit/Unit.hpp"
#include "common/game_object/unit/bonus/Bonus.hpp"

namespace junk {
namespace client {
namespace model {

class Bonus : public virtual Unit, public virtual junk::common::Bonus {
  MODEL_GAME_OBJECT_DEF(Bonus)

 public:
  Bonus();
  virtual ~Bonus();

  void applyBonusPatch(const BonusPatch& bonusPatch);

};  // Bonus

}  // namespace model
}  // namespace client
}  // namespace junk

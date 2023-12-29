#include "Bonus.hpp"

#include "common/logger/Logger.hpp"

namespace junk {
namespace client {
namespace model {

MODEL_GAME_OBJECT_IMPL(Bonus, bonus, BONUS)

Bonus::Bonus() {}

Bonus::~Bonus() {}

void Bonus::applyBonusPatch(const BonusPatch& bonusPatch) {
  applyUnitPatch(bonusPatch.unitPatch);

  bonusType = bonusPatch.bonusType;

  dbg << "Applying BonusPatch";
  dbg.debug(position.x, " ", position.y);
}

}  // namespace model
}  // namespace client
}  // namespace junk

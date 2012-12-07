#include "Bonus.hpp"
#include "common/logger/Logger.hpp"

namespace junk {
namespace client {
namespace model {

MODEL_GAME_OBJECT_IMPL(Bonus, bonus, BONUS)

Bonus::Bonus()
{
}

Bonus::~Bonus()
{
}

void Bonus::applyBonusPatch(const BonusPatch& bonusPatch)
{
  applyGameObjectPatch(bonusPatch.gameObjectPatch);

  position = common::to_SFML_Vector2f(bonusPatch.position);
  bonusType = bonusPatch.bonusType;

  dbg << "Applying BonusPatch";
  dbg.debug(position.x, " ", position.y);
}

}}} // namespace junk::client::model


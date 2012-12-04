#pragma once

#include "client/model/game_object/GameObject.hpp"
#include "common/game_object/bonus/Bonus.hpp"

namespace junk {
namespace client {
namespace model {

class Bonus : public virtual GameObject, public virtual junk::common::Bonus
{
  MODEL_GAME_OBJECT_DEF(Bonus)

public:
  Bonus();
  virtual ~Bonus();

  void applyBonusPatch(const BonusPatch& bonusPatch);

}; // Bonus

}}} // namespace junk::client::model

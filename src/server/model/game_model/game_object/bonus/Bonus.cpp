#include "Bonus.hpp"
#include "common/utils/Convert.hpp"

#include <iostream>

namespace junk {
namespace server {
namespace model {

Bonus::Bonus()
{
}

Bonus::~Bonus()
{
}

Patch Bonus::getPatch()
{
  Patch patch;
  patch.id = id;
  patch.gameObjectType = GameObjectType::BONUS;
  patch.bonusPatch = getBonusPatch();
  return patch;
}

BonusPatch Bonus::getBonusPatch()
{
  BonusPatch bonusPatch;
  bonusPatch.gameObjectPatch = getGameObjectPatch();

  bonusPatch.position = common::to_thrift_Vector2f(position);

  return bonusPatch;
}

void Bonus::destroy()
{
}

void Bonus::startDestruction()
{
  destroyInfo.isDestroyed = true;
  destroyInfo.destroyCountdown = 5;
}

int Bonus::getType()
{
    return TYPE_BONUS;
}

void Bonus::init()
{

}

}}} // namespace junk::server::model


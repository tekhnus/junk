#pragma once

#include "GameObject.hpp"
#include "common/game_object/unit/Unit.hpp"

namespace junk {
namespace client {
namespace model {

class Unit : public virtual GameObject, public virtual junk::common::Unit
{
public:
    Unit();
    virtual ~Unit();

    virtual void applyPatch(const Patch& patch);
    void applyUnitPatch(const UnitPatch& unitPatch);

}; // Unit

}}} // namespace junk::client::model

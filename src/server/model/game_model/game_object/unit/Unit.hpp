#pragma once

#include "server/model/game_model/game_object/GameObject.hpp"
#include "common/game_object/unit/Unit.hpp"

namespace junk {
namespace server {
namespace model {

class Unit : public virtual GameObject, public virtual junk::common::Unit
{
public:
    Unit();
    virtual ~Unit();

    virtual Patch getPatch();
    UnitPatch getUnitPatch();

}; // Unit

}}} // namespace junk::server::model

#pragma once

#include "Unit.hpp"
#include "common/game_object/unit/player/Player.hpp"

namespace junk {
namespace server {
namespace model {

class Player : public virtual Unit, public virtual junk::common::Player
{
public:
    Player();
    virtual ~Player();

    virtual Patch getPatch();
    PlayerPatch getPlayerPatch();

}; // Player

}}} // namespace junk::server::model

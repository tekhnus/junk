#pragma once

#include "server/model/game_model/game_object/unit/Unit.hpp"
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
    virtual void process();

    b2Vec2 force;
    double angularImpulse;
    double torque;

}; // Player

}}} // namespace junk::server::model

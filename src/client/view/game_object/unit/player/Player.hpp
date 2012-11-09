#pragma once

#include "Unit.hpp"
#include "common/game_object/unit/player/Player.hpp"

namespace junk {
namespace client {
namespace view {

class Player : public virtual Unit, public virtual junk::common::Player
{
public:
    Player();
    virtual ~Player();

    virtual void applyPatch(const Patch& patch);
    void applyPlayerPatch(const PlayerPatch& playerPatch);

}; // Player

}}} // namespace junk::client::view

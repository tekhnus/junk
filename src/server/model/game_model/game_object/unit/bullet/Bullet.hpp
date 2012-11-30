#pragma once

#include "server/model/game_model/game_object/unit/Unit.hpp"
#include "common/game_object/unit/bullet/Bullet.hpp"
#include "server/model/game_model/game_object/unit/player/Player.hpp"

namespace junk {
namespace server {
namespace model {

class Bullet : public virtual Unit, public virtual junk::common::Bullet
{
public:
    Bullet(Player* creator);
    virtual ~Bullet();

    virtual void init();

    virtual Patch getPatch();
    BulletPatch getBulletPatch();

    virtual void process();
    virtual void startDestruction();

    virtual int getType();

}; // Bullet

}}} // namespace junk::server::model

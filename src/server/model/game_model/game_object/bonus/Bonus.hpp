#pragma once

#include "server/model/game_model/game_object/GameObject.hpp"
#include "common/game_object/bonus/Bonus.hpp"

#include <Box2D/Box2D.h>

namespace junk {
namespace server {
namespace model {

class Bonus : public virtual GameObject, public virtual junk::common::Bonus
{
public:
    Bonus(b2World *world);
    virtual ~Bonus();

    BonusPatch getBonusPatch();

    virtual void process();
    virtual void destroy();
    virtual void startDestruction();

    virtual int getType();
    virtual void init();

    b2Body* body;

}; // Bonus

}}} // namespace junk::server::model

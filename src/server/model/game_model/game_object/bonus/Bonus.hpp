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
    Bonus();
    virtual ~Bonus();

    virtual Patch getPatch();
    BonusPatch getBonusPatch();

    virtual void destroy();
    virtual void startDestruction();

    virtual int getType();
    virtual void init();

}; // Bonus

}}} // namespace junk::server::model

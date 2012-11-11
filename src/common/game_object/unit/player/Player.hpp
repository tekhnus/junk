#pragma once

#include "common/game_object/unit/Unit.hpp"

namespace junk {
namespace common {

class Player : public virtual Unit
{
public:
    Player();
    virtual ~Player();
};

}} // namespace junk::common

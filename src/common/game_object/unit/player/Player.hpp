#pragma once

#include "Unit.hpp"

namespace junk {
namespace common {

class Player : public virtual Unit
{
public:
    Player();
    virtual ~Player();
};

}} // namespace junk::common

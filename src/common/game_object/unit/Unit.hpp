#pragma once

#include "GameObject.hpp"

namespace junk {
namespace common {

class Unit : public virtual GameObject
{
public:
    Unit();
    virtual ~Unit();

private:
    Vector2f position;
    Vector2f direction;
};

}} // namespace junk::common

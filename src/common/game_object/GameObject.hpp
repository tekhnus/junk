#pragma once

#include <SFML/System.hpp>
#include <cstdint>

namespace junk {
namespace common {

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    int32_t getId() const;

private:
    int32_t id;

}; // GameObject

}} // namespace junk::common

#pragma once

namespace junk {
namespace common {

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

private:
    int32_t id;

}; // GameObject

}} // namespace junk::common

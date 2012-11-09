#pragma once

#include "common/game_object/GameObject.hpp"
#include <gen-cpp/Patches_types.h>

namespace junk {
namespace server {
namespace model {

class GameObject : public virtual junk::common::GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual Patch getPatch();
    GameObjectPatch getGameObjectPatch();

}; // GameObject

}}} // namespace junk::client::model

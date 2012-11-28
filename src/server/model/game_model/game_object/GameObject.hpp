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

    virtual void process() = 0;
    virtual void destroy() = 0;
    virtual void startDestruction() = 0;

}; // GameObject

}}} // namespace junk::client::model

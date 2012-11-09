#pragma once

#include "common/game_object/GameObject.hpp"
#include <gen-cpp/Patches_types.h>

namespace junk {
namespace client {
namespace view {

class GameObject : public virtual junk::common::GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void applyPatch(const Patch& patch);
    void applyGameObjectPatch(const GameObjectPatch& gameObjectPatch);

}; // GameObject

}}} // namespace junk::client::view

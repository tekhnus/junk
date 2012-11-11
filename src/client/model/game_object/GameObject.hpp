#pragma once

#include "common/game_object/GameObject.hpp"
#include <gen-cpp/Patches_types.h>

#include <boost/signals2.hpp>

namespace junk {
namespace client {
namespace model {

class GameObject : public virtual junk::common::GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void applyPatch(const Patch& patch);
    void applyGameObjectPatch(const GameObjectPatch& gameObjectPatch);

    boost::signals2::signal<void (const GameObject&)> updateSignal;

}; // GameObject

}}} // namespace junk::client::model

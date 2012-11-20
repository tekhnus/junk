#pragma once

#include "common/game_object/GameObject.hpp"
#include "common/utils/Convert.hpp"
#include <gen-cpp/Patches_types.h>

#include <boost/signals2.hpp>

#define MODEL_GAME_OBJECT_DEF( _name ) \
public: virtual void applyPatch(const Patch& patch);

#define MODEL_GAME_OBJECT_IMPL( _Name, _name, _NAME) \
void _Name::applyPatch(const Patch& patch) \
{ \
  apply ##_Name ## Patch(patch._name##Patch); \
  updateSignal(*this); \
}

namespace junk {
namespace client {
namespace model {

class GameObject : public virtual junk::common::GameObject
{
  MODEL_GAME_OBJECT_DEF(GameObject)

public:

  GameObject();
  virtual ~GameObject();

  void applyGameObjectPatch(const GameObjectPatch& gameObjectPatch);

  boost::signals2::signal<void (const GameObject&)> updateSignal;

}; // GameObject

}}} // namespace junk::client::model

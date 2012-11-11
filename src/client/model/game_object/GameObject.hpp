#pragma once

#include "common/game_object/GameObject.hpp"
#include <gen-cpp/Patches_types.h>
#include "GameObjectFactory.hpp"

#include <boost/signals2.hpp>

namespace junk {
namespace client {
namespace model {

#define MODEL_GAME_OBJECT_DEF( _name ) \
public: virtual void applyPatch(const Patch& patch);  \

#define MODEL_GAME_OBJECT_IMPL( _Name, _name ) \
void _Name##::applyPatch(const Patch& patch) \
{ \
  apply ## _Name ## Patch(patch. ## _name ## Patch); \
  updateSignal(this); \
} \
static bool _name ## _creator_registred = \
  GameObjectFactory::registerCreator(_name, std::function(new ##_name())); \

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

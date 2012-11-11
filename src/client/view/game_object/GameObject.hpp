#pragma once

#include "common/game_object/GameObject.hpp"
#include "client/model/game_object/GameObject.hpp"
#include "GameObjectFactory.hpp"
#include <gen-cpp/Patches_types.h>

#include <boost/signals2.hpp>

#define VIEW_GAME_OBJECT_DEF( _name ) \
public: \
virtual void update(const model::GameObject& gameObject);

#define VIEW_GAME_OBJECT_IMPL( _Name, _name, _NAME )
//void _Name::update(const model::GameObject& gameObject) \
//{ }
  //update ## _Name (reinterpret_cast<const model::_Name&> gameObject); \
//static bool _name ## _creator_registred = \
  //GameObjectFactory::registerCreator(_Name ## Type::_NAME, std::function(new _Name())); \

namespace junk {
namespace client {
namespace view {

class GameObject : public virtual common::GameObject
{
  VIEW_GAME_OBJECT_DEF(GameObject)

public:
  GameObject();
  virtual ~GameObject();

  void virtual setModelObject(model::GameObject* gameObject);

  void updateGameObject(const model::GameObject& gameObject);

}; // GameObject

}}} // namespace junk::client::view

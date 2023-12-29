#pragma once

#include <gen-cpp/Patches_types.h>

#include <SFML/Graphics.hpp>
#include <boost/signals2.hpp>

#include "client/model/game_object/GameObject.hpp"
#include "common/game_object/GameObject.hpp"

#define VIEW_GAME_OBJECT_DEF(_name) \
 public:                            \
  virtual void update(const model::GameObject& gameObject);

#define VIEW_GAME_OBJECT_IMPL(_Name, _name, _NAME)                \
  void _Name::update(const model::GameObject& gameObject) {       \
    update##_Name(dynamic_cast<const model::_Name&>(gameObject)); \
  }

namespace junk {
namespace client {
namespace view {

class GameObject : public virtual common::GameObject,
                   public virtual sf::Drawable {
  VIEW_GAME_OBJECT_DEF(GameObject)

 public:
  GameObject();
  virtual ~GameObject();

  void virtual setModelObject(model::GameObject* gameObject);

  void updateGameObject(const model::GameObject& gameObject);

};  // GameObject

}  // namespace view
}  // namespace client
}  // namespace junk

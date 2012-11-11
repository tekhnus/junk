#pragma once

#include "common/game_object/GameObject.hpp"
#include "client/model/game_object/GameObject.hpp"
#include <gen-cpp/Patches_types.h>

#include <boost/signals2.hpp>

namespace junk {
namespace client {
namespace view {

class GameObject : public virtual common::GameObject
{
public:
  GameObject();
  virtual ~GameObject();

  virtual setModelObject(model::GameObject& gameObject);
  virtual update(const model::GameObject& gameObject);

  void updateGameObject(const model::GameObject& gameObject);

}; // GameObject

}}} // namespace junk::client::view

#include "GameObject.hpp"

namespace ph = boost::placeholders;

namespace junk {
namespace client {
namespace view {

VIEW_GAME_OBJECT_IMPL(GameObject, gameObject, GAME_OBJECT)

GameObject::GameObject() {}

GameObject::~GameObject() {}

void GameObject::setModelObject(model::GameObject* gameObject) {
  gameObject->updateSignal.connect(
      boost::bind(&GameObject::update, this, ph::_1));
}

void GameObject::updateGameObject(const model::GameObject& gameObject) {
  if (gameObject.destroyInfo.isDestructing) {
    destroyInfo.isDestructing = true;
    destroyInfo.destroyCountdown = gameObject.destroyInfo.destroyCountdown;
  }
}

}  // namespace view
}  // namespace client
}  // namespace junk

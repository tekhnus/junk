#include "GameObject.hpp"

namespace junk {
namespace client {
namespace view {

VIEW_GAME_OBJECT_IMPL(GameObject, gameObject, GAME_OBJECT)

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::setModelObject(model::GameObject* gameObject)
{
  gameObject->updateSignal.connect(boost::bind(&GameObject::update, this, _1));
}

void GameObject::updateGameObject(const model::GameObject& gameObject)
{
}

}}} // namespace junk::client::view

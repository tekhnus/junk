#include "GameObject.hpp"

namespace junk {
namespace client {
namespace view {

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

GameObject::setModelObject(model::GameObject& gameObject)
{
  gameObject.updateSignal.connect(boost::bind(&GameObject::update, this, _1));
}

GameObject::update(const model::GameObject& gameObject)
{
  updateGameObject(reinterpret_cast<const model::GameObject&> gameObject);
}

void GameObject::updateGameObject(const model::GameObject& gameObject)
{
}

} // namespace junk::client::view

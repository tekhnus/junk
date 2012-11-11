#include "Player.hpp"

namespace junk {
namespace client {
namespace view {

Player::Player()
{
}

Player::~Player()
{
}

Player::update(const model::GameObject& gameObject)
{
  updatePlayer(reinterpret_cast<const model::Player&> gameObject);
}

void Player::updatePlayer(const model::Player& player)
{
}

}}} // namespace junk::client::view

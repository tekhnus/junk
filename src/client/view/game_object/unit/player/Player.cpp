#include "Player.hpp"

namespace junk {
namespace client {
namespace view {

VIEW_GAME_OBJECT_IMPL(Player, player, PLAYER)

Player::Player() : body(15)
{
  body.setFillColor(sf::Color::Green);
}

Player::~Player()
{
}

#include <iostream>
void Player::updatePlayer(const model::Player& player)
{
  std::cerr << "I'm being updated!" << std::endl;
  std::cerr << player.position.x << " " << player.position.y << std::endl;
  body.setPosition(player.position);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  std::cerr << "I'm being drawn!" << std::endl;
  target.draw(body, states);
}

}}} // namespace junk::client::view

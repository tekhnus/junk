#include "Player.hpp"

namespace junk {
namespace client {
namespace view {

VIEW_GAME_OBJECT_IMPL(Player, player, PLAYER)

Player::Player() : body(150)
{
  body.setFillColor(sf::Color::Green);
}

Player::~Player()
{
}

void Player::updatePlayer(const model::Player& player)
{
    body.setPosition(player.position);
}

#include <iostream>
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  std::cerr << "I'm being drawn!" << std::endl;
  target.draw(body, states);
}

}}} // namespace junk::client::view

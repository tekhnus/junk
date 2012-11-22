#include "Player.hpp"

namespace junk {
namespace client {
namespace view {

VIEW_GAME_OBJECT_IMPL(Player, player, PLAYER)

Player::Player() : body(20), inner(12), gun(sf::Vector2f(25.0, 4.0))
{
    body.setOrigin(sf::Vector2f(body.getRadius(), body.getRadius()));
    inner.setOrigin(sf::Vector2f(inner.getRadius(), inner.getRadius()));

    body.setFillColor(sf::Color::Yellow);
    inner.setFillColor(sf::Color::Cyan);

    body.setOutlineThickness(2.0);
    body.setOutlineColor(sf::Color::Green);

    inner.setOutlineThickness(1);
    inner.setOutlineColor(sf::Color::Black);

    gun.setFillColor(sf::Color::Red);

    gun.setOrigin(sf::Vector2f(1.0, gun.getSize().y / 2.0));
}

Player::~Player()
{
}

#include <iostream>
void Player::updatePlayer(const model::Player& player)
{
  std::cerr << "I'm being updated!" << std::endl;
  std::cerr << player.position.x << " " << player.position.y << std::endl;
  std::cerr << player.direction.x << " " << player.direction.y << std::endl;
  std::cerr << "gun rotation: " + std::to_string(gun.getRotation()) << std::endl;

  body.setPosition(20.0f * player.position);
  inner.setPosition(body.getPosition());
  gun.setPosition(body.getPosition());
  sf::Vector2f direction = player.direction;

  gun.setRotation((atan2(direction.y, direction.x) * 180) / M_PI);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  std::cerr << "I'm being drawn!" << std::endl;
  target.draw(body, states);
  target.draw(inner, states);
  target.draw(gun, states);
}

}}} // namespace junk::client::view

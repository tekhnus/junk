#include "Player.hpp"
#include "common/logger/Logger.hpp"

namespace junk {
namespace client {
namespace view {

VIEW_GAME_OBJECT_IMPL(Player, player, PLAYER)

Player::Player() : body(1), inner(12 / 20.0), gun(sf::Vector2f(25.0 / 20.0, 4.0 / 20.0 ))
{
    body.setOrigin(sf::Vector2f(body.getRadius(), body.getRadius()));
    inner.setOrigin(sf::Vector2f(inner.getRadius(), inner.getRadius()));

    body.setFillColor(sf::Color::Yellow);
    inner.setFillColor(sf::Color::Cyan);

    body.setOutlineThickness(2.0 / 20.0);
    body.setOutlineColor(sf::Color::Green);

    inner.setOutlineThickness(1 / 20.0);
    inner.setOutlineColor(sf::Color::Black);

    gun.setFillColor(sf::Color::Red);
    gun.setOrigin(sf::Vector2f(1.0 / 20.0, gun.getSize().y / 2.0 / 20.0));

    healthBarBackground.setFillColor(sf::Color::Black);
    healthBarBackground.setOutlineColor(sf::Color::White);
    healthBarBackground.setOutlineThickness(1.0 / 20.0);

    healthBar.setFillColor(sf::Color::White);
    healthBar.setOutlineColor(sf::Color::Transparent);
    healthBar.setOutlineThickness(1.0 / 20.0);

    healthBarBackground.setOrigin(sf::Vector2f(body.getRadius(), 8 / 20.0 + body.getRadius()));
    healthBar.setOrigin(healthBarBackground.getOrigin());
}

Player::~Player()
{
}

void Player::updatePlayer(const model::Player& player)
{
  dbg << "I'm being updated!";
  dbg.debug(player.position.x, " ", player.position.y);
  dbg.debug(player.direction.x, " ", player.direction.y);
  dbg.debug("gun rotation: ", std::to_string(gun.getRotation()));

  body.setPosition(player.position);
  inner.setPosition(body.getPosition());
  gun.setPosition(body.getPosition());
  healthBarBackground.setPosition(body.getPosition());
  healthBar.setPosition(body.getPosition());
  sf::Vector2f direction = player.direction;

  setName(player.getName());
  setScore(player.getScore());

  nickname = sf::Text(player.getName(), ClientView::font, 20);
  nickname.setOrigin(sf::Vector2f(nickname.getLocalBounds().width / 2.0, 30 / 20.0 + body.getRadius()));
  nickname.setPosition(body.getPosition());
  nickname.setFillColor(sf::Color::Magenta);

  float healthScale = float(getHealth()) / float(getMaxHealth());

  healthBarBackground.setSize(sf::Vector2f(body.getRadius() * 2, 4.0f / 20.0));
  healthBar.setSize(sf::Vector2f(body.getRadius() * 2 * healthScale, 4.0f / 20.0));

  setHealth(player.getHealth());
  setMaxHealth(player.getMaxHealth());

  gun.setRotation((atan2(direction.y, direction.x) * 180) / M_PI);

  if (player.destroyInfo.isDestructing)
  {
    destroyInfo.isDestructing = true;
    destroyInfo.destroyCountdown = player.destroyInfo.destroyCountdown;
  }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(body, states);
  target.draw(inner, states);
  target.draw(gun, states);
  target.draw(healthBarBackground, states);
  target.draw(healthBar, states);
  target.draw(nickname, states);
}

}}} // namespace junk::client::view

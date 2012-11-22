#include "Bullet.hpp"

namespace junk {
namespace client {
namespace view {

VIEW_GAME_OBJECT_IMPL(Bullet, bullet, BULLET)

Bullet::Bullet() : body(20.0 / 3)
{
  body.setFillColor(sf::Color::Magenta);
  body.setOrigin(sf::Vector2f(body.getRadius(), body.getRadius()));
}

Bullet::~Bullet()
{
}

#include <iostream>
void Bullet::updateBullet(const model::Bullet& bullet)
{
  body.setPosition(20.0f * bullet.position);
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  std::cerr << "I'm being drawn!" << std::endl;
  target.draw(body, states);
}

}}} // namespace junk::client::view

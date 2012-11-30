#include "Bullet.hpp"
#include "common/logger/Logger.hpp"

namespace junk {
namespace client {
namespace view {

VIEW_GAME_OBJECT_IMPL(Bullet, bullet, BULLET)

Bullet::Bullet() : body(20.0 / 7)
{
  body.setFillColor(sf::Color::Magenta);
  body.setOrigin(sf::Vector2f(body.getRadius(), body.getRadius()));
}

Bullet::~Bullet()
{
}

void Bullet::updateBullet(const model::Bullet& bullet)
{
  body.setPosition(20.0f * bullet.position);
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(body, states);
}

}}} // namespace junk::client::view

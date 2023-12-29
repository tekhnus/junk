#include "Bullet.hpp"

namespace junk {
namespace client {
namespace view {

VIEW_GAME_OBJECT_IMPL(Bullet, bullet, BULLET)

Bullet::Bullet() : body(1.0 / 7) {
  body.setOrigin(sf::Vector2f(body.getRadius(), body.getRadius()));
}

Bullet::~Bullet() {}

void Bullet::updateBullet(const model::Bullet& bullet) {
  body.setPosition(bullet.position);
  type = bullet.type;

  if (type == 0) {
    body.setFillColor(sf::Color::Magenta);
  } else if (type == 1) {
    body.setFillColor(sf::Color::Yellow);
  }

  if (bullet.destroyInfo.isDestructing) {
    destroyInfo.isDestructing = true;
    destroyInfo.destroyCountdown = bullet.destroyInfo.destroyCountdown;
  }
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(body, states);
}

}  // namespace view
}  // namespace client
}  // namespace junk

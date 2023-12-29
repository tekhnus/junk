#pragma once

#include "client/model/game_object/unit/bullet/Bullet.hpp"
#include "client/view/game_object/unit/Unit.hpp"
#include "common/game_object/unit/bullet/Bullet.hpp"

namespace junk {
namespace client {
namespace view {

class Bullet : public virtual Unit, public virtual junk::common::Bullet {
  VIEW_GAME_OBJECT_DEF(Bullet)

 public:
  Bullet();
  virtual ~Bullet();

  void updateBullet(const model::Bullet& bullet);

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
  sf::CircleShape body;

};  // Bullet

}  // namespace view
}  // namespace client
}  // namespace junk

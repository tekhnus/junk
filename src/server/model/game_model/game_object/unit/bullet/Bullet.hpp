#pragma once

#include "common/game_object/unit/bullet/Bullet.hpp"
#include "server/model/game_model/game_object/unit/Unit.hpp"
#include "server/model/game_model/game_object/unit/player/Player.hpp"

namespace junk {
namespace server {
namespace model {

class Bullet : public virtual Unit, public virtual junk::common::Bullet {
  MODEL_GAME_OBJECT_DEF(Bullet)

 public:
  Bullet(Player* creator, int type);
  virtual ~Bullet();

  virtual void init();

  BulletPatch getBulletPatch();

  virtual void process();
  virtual void startDestruction();

  virtual GameObjectType getType();

  const std::string& getOwner() const;
  void setOwner(const std::string& owner);

 private:
  std::string owner;

};  // Bullet

}  // namespace model
}  // namespace server
}  // namespace junk

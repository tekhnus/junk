#pragma once

#include <box2d/box2d.h>
#include <gen-cpp/ClientService.h>

#include "common/game_object/unit/player/Player.hpp"
#include "server/model/game_model/game_object/unit/Unit.hpp"

namespace junk {
namespace server {
namespace model {

class Player : public virtual Unit, public virtual junk::common::Player {
  MODEL_GAME_OBJECT_DEF(Player)

 public:
  Player();
  virtual ~Player();

  PlayerPatch getPlayerPatch();
  virtual void process();
  virtual GameObjectType getType();
  virtual void onBulletHit(int type, const std::string& owner);
  virtual void onBonusEat(int bonusType);

  bool canSee(GameObject* gameObject);

  virtual void init();

  virtual void rotate(const RotateAction& rotateAction);
  virtual void move(const MoveAction& moveAction);
  virtual void fire(const FireAction& fireAction);
  virtual void changeSettings(const ChangeSettingsAction& changeSettingsAction);

  b2Vec2 force;
  double forceFactor;
  double angularImpulse;
  double torque;
  bool fireOn;
  int bulletsType;

  std::chrono::high_resolution_clock::time_point slowDownTime;
  std::chrono::high_resolution_clock::time_point defaultBulletsTime;

 private:
  virtual void processFire();

};  // Player

}  // namespace model
}  // namespace server
}  // namespace junk

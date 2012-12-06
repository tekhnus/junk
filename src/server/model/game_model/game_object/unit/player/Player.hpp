#pragma once

#include "server/model/game_model/game_object/unit/Unit.hpp"
#include "common/game_object/unit/player/Player.hpp"
#include <gen-cpp/ClientService.h>
#include "common/utils/Convert.hpp"

namespace junk {
namespace server {
namespace model {

class Player : public virtual Unit, public virtual junk::common::Player
{
  MODEL_GAME_OBJECT_DEF(Player)

public:
  Player();
  virtual ~Player();

  PlayerPatch getPlayerPatch();
  virtual void process();
  virtual int getType();
  virtual void onBulletHit();

  virtual void init();

  virtual void rotate(const RotateAction& rotateAction);
  virtual void move(const MoveAction& moveAction);
  virtual void fire(const FireAction& fireAction);

  b2Vec2 force;
  double angularImpulse;
  double torque;
  bool fireOn;

private:
  virtual void processFire();

}; // Player

}}} // namespace junk::server::model

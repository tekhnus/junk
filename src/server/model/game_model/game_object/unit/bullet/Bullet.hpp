#pragma once

#include "server/model/game_model/game_object/unit/Unit.hpp"
#include "common/game_object/unit/bullet/Bullet.hpp"
#include "server/model/game_model/game_object/unit/player/Player.hpp"

namespace junk {
namespace server {
namespace model {

class Bullet : public virtual Unit, public virtual junk::common::Bullet
{
  MODEL_GAME_OBJECT_DEF(Bullet)

public:
<<<<<<< HEAD
  Bullet(Player* creator);
  virtual ~Bullet();

  virtual void init();

  BulletPatch getBulletPatch();
=======
    Bullet(Player* creator);
    virtual ~Bullet();

    virtual void init();

    virtual Patch getPatch();
    BulletPatch getBulletPatch();
>>>>>>> Removed functionality from SGM

  virtual void process();
  virtual void startDestruction();

  virtual int getType();

}; // Bullet

}}} // namespace junk::server::model

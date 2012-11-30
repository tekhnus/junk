#pragma once

#include "common/game_object/GameObject.hpp"
#include "gen-cpp/Patches_types.h"
//#include "server/model/game_model/ServerGameModel.hpp"

namespace junk {
namespace server {
namespace model {

extern int TYPE_PLAYER;
extern int TYPE_BULLET;

class ServerGameModel;

class GameObject : public virtual junk::common::GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void init() = 0;

    virtual Patch getPatch();
    GameObjectPatch getGameObjectPatch();

    virtual void process();
    virtual void destroy() = 0;
    virtual void startDestruction() = 0;

    virtual int getType() = 0;

    ServerGameModel* model;
    int lifetime;

}; // GameObject

}}} // namespace junk::client::model

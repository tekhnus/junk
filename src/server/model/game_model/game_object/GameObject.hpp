#pragma once

#include "common/game_object/GameObject.hpp"
#include "gen-cpp/Patches_types.h"
//#include "server/model/game_model/ServerGameModel.hpp"

namespace junk {
namespace server {
namespace model {

class ServerGameModel;

class GameObject : public virtual junk::common::GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual Patch getPatch();
    GameObjectPatch getGameObjectPatch();

    virtual void process();

    ServerGameModel* model;
    int lifetime;

}; // GameObject

}}} // namespace junk::client::model

#pragma once

#include <SFML/System.hpp>
#include <boost/signals2.hpp>
#include <common/logger/Logger.hpp>
#include "network_model/ClientNetworkModel.hpp"
#include "game_object/GameObject.hpp"
#include "game_object/GameObjectFactory.hpp"

#include <unordered_map>

namespace junk {
namespace client {
namespace model {

class ClientModel
{
public:
  ClientModel();
  ~ClientModel();

  int32_t connectToServer(const std::string& serverIp, int port);

  void update();

  void addGameObject(const Patch &patch);

  void makeAction(const Action& action);

  boost::signals2::signal<void (int32_t)> gotClientIdSignal;
  boost::signals2::signal<void (const GameObjectType::type&, GameObject*)> gameObjectAddedSignal;

private:
  struct ClientInfo
  {
    ClientInfo(int32_t id = -1): id(id) {}
    int32_t id;
  };

  GameObjectFactory gameObjectFactory;
  std::unordered_map< int32_t, std::unique_ptr<GameObject> > gameObjects;

  ClientNetworkModel networkModel;

  ClientInfo clientInfo;

  Logger logger;

}; // ClientModel

}}} // namespace junk::client::model

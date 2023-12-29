#pragma once

#include <SFML/System.hpp>
#include <boost/signals2.hpp>
#include <common/logger/Logger.hpp>
#include <unordered_map>

#include "game_object/GameObject.hpp"
#include "game_object/GameObjectFactory.hpp"
#include "network_model/ClientNetworkModel.hpp"

namespace junk {
namespace client {
namespace model {

class ClientModel {
 public:
  ClientModel();
  ~ClientModel();

  void reset();

  void shutdown();

  int32_t connectToServer(const std::string& serverIp, int port);

  void update();
  void removeObsoleteGameObjects();

  void addGameObject(const Patch& patch);
  void removeGameObject(int32_t id);

  void makeAction(const Action& action);

  boost::signals2::signal<void(int32_t)> gotClientIdSignal;
  boost::signals2::signal<void(const GameObjectType::type&, GameObject*)>
      gameObjectAddedSignal;
  boost::signals2::signal<void()> shutdownSignal;

  bool alive;

  std::unordered_map<int32_t, std::unique_ptr<GameObject> > gameObjects;

 private:
  struct ClientInfo {
    ClientInfo(int32_t id = -1) : id(id) {}
    int32_t id;
  };

  GameObjectFactory gameObjectFactory;

  ClientNetworkModel networkModel;

  ClientInfo clientInfo;

  Logger logger;

};  // ClientModel

}  // namespace model
}  // namespace client
}  // namespace junk

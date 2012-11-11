#pragma once

#include <SFML/System.hpp>
#include <boost/signals2.hpp>
#include <common/logger/Logger.hpp>
#include "network_model/ClientNetworkModel.hpp"
#include "game_object/GameObject.hpp"

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

  void addGameObject(int32_t id);
  void updatePlayerPosition(int32_t id, sf::Vector2f position);
  void updatePlayerDirection(int32_t id, sf::Vector2f direction);

  void makeAction(const Action& action);

  boost::signals2::signal<void (int32_t)> gotClientIdSignal;
  boost::signals2::signal<void (int32_t, GameObject*)> gameObjectAddedSignal;
  boost::signals2::signal<void (int32_t, sf::Vector2f)> clientPositionUpdatedSignal;
  boost::signals2::signal<void (int32_t, sf::Vector2f)> clientDirectionUpdatedSignal;

private:
  struct ClientInfo
  {
    ClientInfo(int32_t id = -1): id(id) {}
    int32_t id;
  };

  std::unordered_map< int32_t, std::unique_ptr<GameObject> > gameObjects;
  ClientNetworkModel networkModel;

  ClientInfo clientInfo;

  Logger logger;

}; // ClientModel

}}} // namespace junk::client::model

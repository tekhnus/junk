#pragma once

#include <SFML/System.hpp>
#include <boost/signals2.hpp>
#include <common/logger/Logger.hpp>
#include "network_model/ClientNetworkModel.hpp"

#include <unordered_map>

namespace junk
{

class Player
{
public:

  Player()
  {
  }

  Player(int32_t id, sf::Vector2f position, sf::Vector2f direction) : id(id), position(position), direction(direction)
  {
  }

  void setPosition(sf::Vector2f position)
  {
    this->position = position;
  }

  void setDirection(sf::Vector2f direction)
  {
    this->direction = direction;
  }

  int32_t getId() const
  {
    return id;
  }

private:
  int32_t id;
  sf::Vector2f position;
  sf::Vector2f direction;
};

class ClientModel
{
public:
  ClientModel();
  ~ClientModel();

  int32_t connectToServer(const std::string& serverIp, int port);

  void update();

  void addPlayer(int32_t id, sf::Vector2f position, sf::Vector2f direction);
  void updatePlayerPosition(int32_t id, sf::Vector2f position);
  void updatePlayerDirection(int32_t id, sf::Vector2f direction);

  void makeAction(const Action& action);

  boost::signals2::signal<void (int32_t)> gotClientIdSignal;
  boost::signals2::signal<void (int32_t, sf::Vector2f, sf::Vector2f)> clientAddedSignal;
  boost::signals2::signal<void (int32_t, sf::Vector2f)> clientPositionUpdatedSignal;
  boost::signals2::signal<void (int32_t, sf::Vector2f)> clientDirectionUpdatedSignal;

private:
  struct ClientInfo
  {
    ClientInfo(int32_t id = -1): id(id) {}
    int32_t id;
  };

  std::unordered_map<int32_t, Player> players;
  ClientNetworkModel networkModel;

  ClientInfo clientInfo;

  Logger logger;

}; // ClientModel

} // namespace junk

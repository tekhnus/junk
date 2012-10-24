#pragma once

#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include <common/logger/Logger.hpp>
#include "network_model/ClientNetworkModel.hpp"

namespace junk
{

class Player
{
public:
	Player(int32_t id) : id(id) {}

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
	sf::Vector2f position;
	sf::Vector2f direction;
	int32_t id;
};

class ClientModel
{
public:
  ClientModel();
  ~ClientModel();

  void connectToServer(const std::string& serverIp, int port);

  void update();

  void addPlayer(int32_t id);
	void updatePlayerPosition(int32_t id, sf::Vector2f position);
	void updatePlayerDirection(int32_t id, sf::Vector2f direction);

	void subscribeForClientAddedSignal(sigc::slot<void, int32_t> slot);
	void subscribeForClientPositionUpdatedSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);
	void subscribeForClientDirectionUpdatedSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);

	void move(sf::Vector2f direction);
	void rotate(sf::Vector2f direction);
	void fire(sf::Vector2f direction);

private:
	std::vector<Player> players;
	ClientNetworkModel networkModel;
	int32_t clientId;

	sigc::signal<void, int32_t> clientAddedSignal;
	sigc::signal<void, int32_t, sf::Vector2f> clientPositionUpdatedSignal;
	sigc::signal<void, int32_t, sf::Vector2f> clientDirectionUpdatedSignal;

  Logger logger;
  
}; // ClientModel

} // namespace junk

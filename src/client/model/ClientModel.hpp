#pragma once

#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include <common/logger/Logger.hpp>
#include "network_model/ClientNetworkModel.hpp"

#include <unordered_map>

namespace junk
{

class Player
{
public:
	Player() {}
	Player(int32_t id, sf::Vector2f position, sf::Vector2f direction) : id(id), position(position), direction(direction) {}

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

  void connectToServer(const std::string& serverIp, int port);

  void update();

  void addPlayer(int32_t id, sf::Vector2f position, sf::Vector2f direction);
	void updatePlayerPosition(int32_t id, sf::Vector2f position);
	void updatePlayerDirection(int32_t id, sf::Vector2f direction);

	void subscribeForClientAddedSignal(sigc::slot<void, int32_t, sf::Vector2f, sf::Vector2f> slot);
	void subscribeForClientPositionUpdatedSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);
	void subscribeForClientDirectionUpdatedSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);

	void move(sf::Vector2f direction);
	void rotate(sf::Vector2f direction);
	void fire(sf::Vector2f direction);

private:
	std::unordered_map<int32_t, Player> players;
	ClientNetworkModel networkModel;
	int32_t clientId;

	sigc::signal<void, int32_t, sf::Vector2f, sf::Vector2f> clientAddedSignal;
	sigc::signal<void, int32_t, sf::Vector2f> clientPositionUpdatedSignal;
	sigc::signal<void, int32_t, sf::Vector2f> clientDirectionUpdatedSignal;

  Logger logger;
  
}; // ClientModel

} // namespace junk

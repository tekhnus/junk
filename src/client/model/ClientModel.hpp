#pragma once

#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include <common/logger/Logger.hpp>
#include <common/server_service/ServerServiceHandler.hpp>

namespace junk
{

class Player
{
public:
	void setPosition(sf::Vector2f position)
	{
		this->position = position;
	}

	void setDirection(sf::Vector2f direction)
	{
		this->direction = direction;
	}

	int16_t getId() const
	{
		return id;
	}

private:
	sf::Vector2f position;
	sf::Vector2f direction;
	int16_t id;
};

class ClientModel
{
public:
  ClientModel();
  ~ClientModel();

	void updatePlayerPosition(int16_t id, sf::Vector2f position);
	void updatePlayerDirection(int16_t id, sf::Vector2f direction);

	void subscribeForClientPositionUpdatedSignal(sigc::slot<void, int16_t, sf::Vector2f> slot);
	void subscribeForClientDirectionUpdatedSignal(sigc::slot<void, int16_t, sf::Vector2f> slot);

private:
	std::vector<Player> players;
	ServerServiceHandler serverService;
	int16_t clientId;

	sigc::signal<void, int16_t, sf::Vector2f> clientPositionUpdatedSignal;
	sigc::signal<void, int16_t, sf::Vector2f> clientDirectionUpdatedSignal;

  Logger logger;
  
}; // ClientModel

} // namespace junk

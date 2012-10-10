#pragma once

#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include <logger/Logger.hpp>
#include <client/model/ServerServiceHandler.hpp>

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

	int getId() const
	{
		return id;
	}

private:
	sf::Vector2f position;
	sf::Vector2f direction;
	int id;
};

class ClientModel
{
public:
  ClientModel();
  ~ClientModel();

	void updatePlayerPosition(int id, sf::Vector2f position);
	void updatePlayerDirection(int id, sf::Vector2f direction);

private:
	std::vector<Player> players;
	ServerServiceHandler serverService;
	int clientId;

  Logger logger;
  
}; // ClientModel

} // namespace junk
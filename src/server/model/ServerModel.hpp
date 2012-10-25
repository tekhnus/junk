#pragma once

#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include <common/logger/Logger.hpp>
#include "network_model/ServerNetworkModel.hpp"
#include "game_model/ServerGameModel.hpp"

namespace junk
{

class ServerModel
{
public:
  ServerModel();
  ~ServerModel();

  void start();

private:

	GameChanges getChangesHandler(int32_t id);
	int connectHandler();
	void moveHandler(int32_t id, sf::Vector2f direction);
	void rotateHandler(int32_t id, sf::Vector2f direction);
	void fireHandler(int32_t id, sf::Vector2f direction);

	ServerNetworkModel networkModel;
	ServerGameModel gameModel;

  Logger logger;
  
}; // ServerModel

} // namespace junk

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
  explicit ServerModel();
  ~ServerModel();

private:
	ServerNetworkModel networkModel;
	ServerGameModel gameModel;


  Logger logger;
  
}; // ServerModel

} // namespace junk

#pragma once

#include "Unit.hpp"
#include "client/model/ClientModel.hpp"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <boost/signals2.hpp>

#include <common/logger/Logger.hpp>

#include <map>
#include <cassert>
#include <memory>

//for std::this_thread::sleep_for
#ifndef _GLIBCXX_USE_NANOSLEEP
	#define _GLIBCXX_USE_NANOSLEEP
#endif

#include <thread>

namespace junk
{

typedef unsigned int IDType;

class ClientView : public sf::Drawable
{
public:
  ClientView();
  virtual ~ClientView();

  void setModel(ClientModel* clientModel);

  void addPlayer(IDType playerID, sf::Vector2f position, sf::Vector2f rotation);
  void removePlayer(IDType playerID);

  void setPlayerPosition(IDType playerID, sf::Vector2f position);
  void setPlayerRotation(IDType playerID, sf::Vector2f rotation);

  void move(sf::Vector2f direction);
  void rotate(sf::Vector2f rotation);

  void setClientID(IDType clientID);
  void update();

  // Kostul'!!!
  std::map<IDType, PlayerUnit> players;

  boost::signals2::signal<void (sf::Vector2f)> fireSignal;
  boost::signals2::signal<void (sf::Vector2f)> moveSignal;
  boost::signals2::signal<void (sf::Vector2f)> rotateSignal;

private:
  IDType clientID;
  void processInput();
  Logger logger;
  std::thread inputThread;
  bool prevUp, prevDown, prevLeft, prevRight;

protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}

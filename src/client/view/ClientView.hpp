#pragma once

#include "Unit.hpp"
#include "client/model/ClientModel.hpp"
#include "game_object/GameObject.hpp"
#include "game_object/GameObjectFactory.hpp"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <boost/signals2.hpp>

#include <common/logger/Logger.hpp>

#include <unordered_map>
#include <cassert>
#include <memory>

//for std::this_thread::sleep_for
#ifndef _GLIBCXX_USE_NANOSLEEP
	#define _GLIBCXX_USE_NANOSLEEP
#endif

#include <thread>

namespace junk {
namespace client {
namespace view {

class ClientView : public sf::Drawable
{
public:
  ClientView();
  virtual ~ClientView();

  void setModel(model::ClientModel* clientModel);

  void addGameObject(const GameObjectType::type &gameObjectType, model::GameObject* gameObject);
  /*
  void removePlayer(int32_t playerID);

  void setPlayerPosition(int32_t playerID, sf::Vector2f position);
  void setPlayerRotation(int32_t playerID, sf::Vector2f rotation);
  */

  void move(sf::Vector2f direction);
  void rotate(sf::Vector2f rotation);

  void makeAction(const Action& action);

  void setClientID(int32_t clientID);
  void update();

  boost::signals2::signal<void (const Action& action)> makeActionSignal;

private:

  GameObjectFactory gameObjectFactory;
  std::unordered_map<int32_t, std::unique_ptr<GameObject> > gameObjects;

  int32_t clientID;
  void processInput();
  Logger logger;
  std::thread inputThread;
  bool prevUp, prevDown, prevLeft, prevRight;

protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}}} // namespace junk::client::view

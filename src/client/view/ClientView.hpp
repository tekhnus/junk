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

void loadFont();

class ClientView : public sf::Drawable
{
public:
  ClientView();
  virtual ~ClientView();

  void setModel(model::ClientModel* clientModel);

  void update();

  int setWindowHeigth(int heigth);
  int setWindowWidth(int width);
  int getWindowHeigth() const;
  int getWindowWidth() const;

  void addGameObject(const GameObjectType::type &gameObjectType, model::GameObject* gameObject);

  void removeObsoleteGameObjects();
  void removeGameObject(int32_t gameObjectId);

  void move(sf::Vector2f direction);
  void rotate(sf::Vector2f direction);
  void fire(bool on);

  void makeAction(Action& action);

  void setClientId(int32_t clientId);

  void shutdown();

  void wake();

  void reset();

  boost::signals2::signal<void (const Action& action)> makeActionSignal;
  mutable std::mutex safe;
  sf::RenderWindow* window;
  static sf::Font font;
  void processInput();
private:

  GameObjectFactory gameObjectFactory;
  std::unordered_map<int32_t, std::unique_ptr<GameObject> > gameObjects;

  int32_t clientId;
  mutable Logger logger;
  bool prevUp, prevDown, prevLeft, prevRight, prevClicked;
  sf::Vector2i prevPos;
  bool alive;
  model::ClientModel* model;

  struct WindowAttributes
  {
    int height, width;
  };

  WindowAttributes windowAttributes;

protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}}} // namespace junk::client::view

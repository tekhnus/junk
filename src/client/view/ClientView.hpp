#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <boost/signals2.hpp>
#include <common/logger/Logger.hpp>
#include <memory>
#include <unordered_map>

#include "client/model/ClientModel.hpp"
#include "game_object/GameObject.hpp"
#include "game_object/GameObjectFactory.hpp"

namespace junk {
namespace client {
namespace view {

void loadFont();

struct WindowAttributes {
  unsigned height, width;
};

class ClientView : public sf::Drawable {
 public:
  ClientView();
  virtual ~ClientView();

  void setModel(model::ClientModel* clientModel);

  void update();

  void setWindowHeigth(unsigned heigth);
  void setWindowWidth(unsigned width);
  unsigned getWindowHeigth() const;
  unsigned getWindowWidth() const;

  void addGameObject(const GameObjectType::type& gameObjectType,
                     model::GameObject* gameObject);

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

  boost::signals2::signal<void(const Action& action)> makeActionSignal;
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

  WindowAttributes windowAttributes;

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}  // namespace view
}  // namespace client
}  // namespace junk

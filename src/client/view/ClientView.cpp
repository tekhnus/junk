#include "ClientView.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "common/utils/Resource.hpp"
#include "game_object/GameObject.hpp"
#include "game_object/unit/player/Player.hpp"

namespace ph = boost::placeholders;

namespace junk {
namespace client {
namespace view {

sf::Font ClientView::font;

void loadFont() {
  ClientView::font.loadFromFile(get_resource_path("arial.ttf"));
}

sf::Vector2f getDiff(bool up, bool down, bool left, bool right) {
  float time = 1;
  float dx = 0;
  float dy = 0;
  if (up) {
    dy += -time;
  }

  if (down) {
    dy += time;
  }

  if (left) {
    dx += -time;
  }

  if (right) {
    dx += time;
  }

  if (fabs(dx) > 0.0 && fabs(dy) > 0.0) {
    dx /= sqrtf(2.0);
    dy /= sqrtf(2.0);
  }
  return sf::Vector2f(dx, dy);
}

ClientView::ClientView()
    : clientId(-1),
      logger("CLIENT_VIEW", "client_view.log", true),
      alive(false) {
  setWindowHeigth(sf::VideoMode::getDesktopMode().height * 2 / 3);
  setWindowWidth(sf::VideoMode::getDesktopMode().width * 2 / 3);
}

ClientView::~ClientView() {
  alive = false;
}

void ClientView::setModel(model::ClientModel* clientModel) {
  makeActionSignal.connect(
      boost::bind(&model::ClientModel::makeAction, clientModel, ph::_1));

  clientModel->gotClientIdSignal.connect(
      boost::bind(&ClientView::setClientId, this, ph::_1));
  clientModel->gameObjectAddedSignal.connect(
      boost::bind(&ClientView::addGameObject, this, ph::_1, ph::_2));
  clientModel->shutdownSignal.connect(boost::bind(&ClientView::shutdown, this));

  model = clientModel;
}

void ClientView::update() {
  removeObsoleteGameObjects();
}

void ClientView::setWindowHeigth(unsigned heigth) {
  windowAttributes.height = heigth;
}

void ClientView::setWindowWidth(unsigned width) {
  windowAttributes.width = width;
}

unsigned ClientView::getWindowHeigth() const {
  return windowAttributes.height;
}

unsigned ClientView::getWindowWidth() const {
  return windowAttributes.width;
}

void ClientView::addGameObject(const GameObjectType::type& gameObjectType,
                               model::GameObject* gameObject) {
  logger << std::string("Adding object ") + std::to_string(gameObject->id);

  gameObjects.insert(std::make_pair(
      gameObject->id,
      std::unique_ptr<GameObject>(gameObjectFactory.create(gameObjectType))));

  gameObjects[gameObject->id]->setModelObject(gameObject);
}

void ClientView::removeObsoleteGameObjects() {
  logger << "removeObsoleteGameObjects()";
  std::vector<int32_t> destroyCandidates;
  for (auto& gameObject : gameObjects) {
    if (gameObject.second->destroyInfo.isDestructing) {
      logger << "destroyCountdown " +
                    std::to_string(
                        gameObject.second->destroyInfo.destroyCountdown);

      if (gameObject.second->destroyInfo.destroyCountdown == 0) {
        destroyCandidates.push_back(gameObject.first);
      }
    }
  }
  for (size_t i = 0; i < destroyCandidates.size(); ++i) {
    logger << "removing " + std::to_string(destroyCandidates[i]);
    gameObjects.erase(destroyCandidates[i]);
  }
}

void ClientView::removeGameObject(int32_t gameObjectId) {
  gameObjects.erase(gameObjectId);
}

void ClientView::makeAction(Action& action) {
  logger << "makeAction invoked";
  action.playerId = clientId;
  makeActionSignal(action);
}

void ClientView::move(sf::Vector2f direction) {
  logger << "move invoked " + std::to_string(direction.x) + " " +
                std::to_string(direction.y);

  Action action;
  action.actionType = ActionType::MOVE;
  action.moveAction.direction.x = direction.x;
  action.moveAction.direction.y = direction.y;
  action.__set_moveAction(action.moveAction);

  makeAction(action);
}

void ClientView::rotate(sf::Vector2f direction) {
  logger << "rotate invoked " + std::to_string(direction.x) + " " +
                std::to_string(direction.y);

  Action action;
  action.actionType = ActionType::ROTATE;
  action.rotateAction.direction.x = direction.x;
  action.rotateAction.direction.y = direction.y;
  action.__set_rotateAction(action.rotateAction);

  makeAction(action);
}

void ClientView::fire(bool on) {
  logger << "fire invoked";

  Action action;
  action.actionType = ActionType::FIRE;
  action.fireAction.on = on;
  action.__set_fireAction(action.fireAction);

  makeAction(action);
}

void ClientView::setClientId(int32_t clientID) {
  logger << std::string("Setting client id to ") + std::to_string(clientID);
  this->clientId = clientID;
}

void ClientView::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  logger << "Drawing. getting shift";
  sf::Vector2f shift;
  sf::Text text;
  bool drawText = false;
  if (model->gameObjects.find(clientId) != model->gameObjects.end()) {
    model::Player* player =
        dynamic_cast<model::Player*>(model->gameObjects[clientId].get());
    shift = -sf::Vector2f(player->position);

    text = sf::Text(std::to_string(player->position.x) + std::string(":") +
                        std::to_string(player->position.y),
                    font, 30);
    text.setFillColor(sf::Color::Magenta);
    text.setPosition(static_cast<float>(target.getSize().x) - 400.0f, 0.0f);
    drawText = true;
  }

  states.transform.translate(sf::Vector2f(window->getSize()) * 0.5f);
  states.transform.scale(40.0f, 40.0f);
  states.transform.translate(shift);

  for (auto& gameObject : gameObjects) {
    // logger.debug(shift.x, " ", shift.y);
    target.draw(*gameObject.second, states);
  }

  if (drawText) {
    target.draw(text);
  }

  // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
  {
    std::vector<std::pair<int, std::string> > scoreBoard;
    for (auto& object : gameObjects) {
      Player* player = dynamic_cast<Player*>(object.second.get());
      if (player != nullptr) {
        dbg.debug("Printing player scores");
        dbg.debug(std::string("Player name is \"") + player->getName() +
                  std::string("\""));

        scoreBoard.push_back(
            std::make_pair(player->getScore(), player->getName()));
      }
    }

    std::sort(scoreBoard.rbegin(), scoreBoard.rend());

    float yCord = 50;
    for (auto& score : scoreBoard) {
      sf::Text text(
          score.second + std::string(" : ") + std::to_string(score.first), font,
          30);
      text.setFillColor(sf::Color::Magenta);
      text.setPosition(10, yCord);
      yCord += 24;

      target.draw(text);
    }
  }
}

void ClientView::reset() {
  gameObjects.clear();
}

void ClientView::processInput(const std::vector<sf::Event>& key_events) {
  if (!alive || clientId == -1) {
    return;
  }

  logger << "Processing input";

  logger << "Processed keyboard";

  bool changed = false;
  bool mouseChanged = false;
  bool mouseMoved = false;
  int mx = 0;
  int my = 0;
  for (const auto& event : key_events) {
    switch (event.type) {
      case sf::Event::KeyPressed:
      case sf::Event::KeyReleased: {
        changed = true;
        bool isPressed = event.type == sf::Event::KeyPressed;
        switch (event.key.code) {
          case sf::Keyboard::Up:
          case sf::Keyboard::W:
            prevUp = isPressed;
            break;
          case sf::Keyboard::Down:
          case sf::Keyboard::S:
            prevDown = isPressed;
            break;
          case sf::Keyboard::Left:
          case sf::Keyboard::A:
            prevLeft = isPressed;
            break;
          case sf::Keyboard::Right:
          case sf::Keyboard::D:
            prevRight = isPressed;
            break;
          default:
            break;
        }
        break;
      }
      case sf::Event::MouseButtonPressed:
      case sf::Event::MouseButtonReleased:
      case sf::Event::MouseMoved: {
        if (event.type == sf::Event::MouseButtonPressed) {
          mouseChanged = true;
          prevClicked = true;
        } else if (event.type == sf::Event::MouseButtonReleased) {
          mouseChanged = true;
          prevClicked = false;
        } else if (event.type == sf::Event::MouseMoved) {
          mouseMoved = true;
          mx = event.mouseMove.x;
          my = event.mouseMove.y;
        }
        break;
      }
      default: {
        break;
      }
    }
  }
  if (changed) {
    sf::Vector2f diff = getDiff(prevUp, prevDown, prevLeft, prevRight);
    move(diff);
  }

  logger << "Processing mouse";

  // TODO(): seems that short mouse clicks don't produce a shot because
  // prevClicked is set and immediately unset.
  if (mouseChanged) {
    fire(prevClicked);
  }

  if (mouseMoved) {
    sf::Vector2i posI{mx, my};
    sf::Vector2f pos = sf::Vector2f(posI);
    // We don't use getWindowWidth() here, because the window could be resized
    // by the player.
    pos -= sf::Vector2f(window->getSize()) * 0.5f;
    rotate(pos);
  }

  logger << "Processed mouse";
}

void ClientView::shutdown() {
  alive = false;
}

void ClientView::wake() {
  alive = true;
}

}  // namespace view
}  // namespace client
}  // namespace junk

#include "ClientView.hpp"

#include "game_object/GameObject.hpp"
#include "game_object/unit/Unit.hpp"
#include "game_object/unit/player/Player.hpp"

namespace junk {
namespace client {
namespace view {

sf::Font createFont()
{
    sf::Font font;
    font.loadFromFile("/usr/local/share/junk/arial.ttf");
    return font;
}

sf::Font ClientView::font(createFont());

sf::Vector2f getDiff(bool up, bool down, bool left, bool right)
{
  float time = 1;
  float dx = 0;
  float dy = 0;
  if (up)
    dy += -time;

  if (down)
    dy += time;

  if (left)
    dx += -time;

  if (right)
    dx += time;

  if (fabs(dx) > 0.0 && fabs(dy) > 0.0)
  {
    dx /= sqrt(2.0);
    dy /= sqrt(2.0);
  }
  return sf::Vector2f(dx, dy);
}

ClientView::ClientView()
: logger("CLIENT_VIEW", "client_view.log", true), clientId(-1)
, inputThread(&ClientView::processInput, this), alive(false)
{
  setWindowHeigth(360);
  setWindowWidth(360);
}

ClientView::~ClientView()
{
  alive = false;
  inputThread.join();
}

void ClientView::setModel(model::ClientModel* clientModel)
{
  makeActionSignal.connect(boost::bind(&model::ClientModel::makeAction, clientModel, _1));

  clientModel->gotClientIdSignal.connect(boost::bind(&ClientView::setClientId, this, _1));
  clientModel->gameObjectAddedSignal.connect(boost::bind(&ClientView::addGameObject, this, _1, _2));
  clientModel->shutdownSignal.connect(boost::bind(&ClientView::shutdown, this));

  model = clientModel;
}

void ClientView::update()
{
    removeObsoleteGameObjects();
}

int ClientView::setWindowHeigth(int heigth)
{
  windowAttributes.height = heigth;
}

int ClientView::setWindowWidth(int width)
{
  windowAttributes.width = width;
}

int ClientView::getWindowHeigth() const
{
  return windowAttributes.height;
}

int ClientView::getWindowWidth() const
{
  return windowAttributes.width;
}

void ClientView::addGameObject(const GameObjectType::type& gameObjectType, model::GameObject* gameObject)
{
  logger << std::string("Adding object ") + std::to_string(gameObject->id);

  gameObjects.insert(std::make_pair(gameObject->id,
    std::unique_ptr<GameObject> (gameObjectFactory.create(gameObjectType))));

  gameObjects[gameObject->id]->setModelObject(gameObject);
}

void ClientView::removeObsoleteGameObjects()
{
  logger << "removeObsoleteGameObjects()";
  std::vector<int32_t> destroyCandidates;
  for (auto& gameObject : gameObjects)
  {
    if (gameObject.second->destroyInfo.isDestructing)
    {
      logger << "destroyCountdown " + std::to_string(gameObject.second->destroyInfo.destroyCountdown);

      if (gameObject.second->destroyInfo.destroyCountdown == 0)
      {
        destroyCandidates.push_back(gameObject.first);
      }
    }
  }
  for (int i = 0; i < destroyCandidates.size(); ++i)
  {
    logger << "removing " + std::to_string(destroyCandidates[i]);
    gameObjects.erase(destroyCandidates[i]);
  }
}

void ClientView::removeGameObject(int32_t gameObjectId)
{
  gameObjects.erase(gameObjectId);
}

void ClientView::makeAction(Action& action)
{
  logger << "makeAction invoked";
  action.playerId = clientId;
  makeActionSignal(action);
}

void ClientView::move(sf::Vector2f direction)
{
  logger << "move invoked " + std::to_string(direction.x) + " " + std::to_string(direction.y);

  Action action;
  action.actionType = ActionType::MOVE;
  action.moveAction.direction.x = direction.x;
  action.moveAction.direction.y = direction.y;
  action.__set_moveAction(action.moveAction);

  makeAction(action);
}

void ClientView::rotate(sf::Vector2f direction)
{
  logger << "rotate invoked " + std::to_string(direction.x) + " " + std::to_string(direction.y);

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

void ClientView::setClientId(int32_t clientID)
{
  logger << std::string("Setting client id to ") + std::to_string(clientID);
  this->clientId = clientID;
}

#include <cassert>
void ClientView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  logger << "Drawing. getting shift";
  sf::Vector2f shift;
  sf::Text text;
  bool drawText = false;
  if (model->gameObjects.find(clientId) != model->gameObjects.end()) {
    model::Player* player = dynamic_cast<model::Player*>(model->gameObjects[clientId].get());
    shift = sf::Vector2f(player->position);

    text = sf::Text(std::to_string(player->position.x) + std::string(":") + std::to_string(player->position.y), font, 20);
    text.setColor(sf::Color::Magenta);
    text.setPosition(target.getSize().x - 200 /*text.getLocalBounds().width*/, 0.0f);
    drawText = true;
  }

  states.transform.translate(shift * -20.0f);
  states.transform.translate(getWindowHeigth(), getWindowWidth());
  for (auto& gameObject : gameObjects)
  {
    //logger.debug(shift.x, " ", shift.y);
    target.draw(*gameObject.second, states);
  }

  if (drawText)
  {
    target.draw(text);
  }

  //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
  {
      std::vector<std::pair<int, std::string> > scoreBoard;
      for (auto& object : gameObjects)
      {
          Player* player = dynamic_cast<Player*>(object.second.get());
          if (player != nullptr)
          {
              dbg.debug("Printing player scores");
              dbg.debug(std::string("Player name is \"") + player->getName() + std::string("\""));

              scoreBoard.push_back(std::make_pair(player->getScore(), player->getName()));
          }
      }

      std::sort(scoreBoard.rbegin(), scoreBoard.rend());

      int yCord = 50;
      for (auto& score : scoreBoard)
      {
          sf::Text text(score.second + std::string(" : ") + std::to_string(score.first), font, 20);
          text.setColor(sf::Color::Magenta);
          text.setPosition(10, yCord);
          yCord += 24;

          target.draw(text);
      }
  }
}

void ClientView::reset()
{
  gameObjects.clear();
}

void ClientView::processInput()
{
  while(true){

  while (alive)
  {
    if (clientId == -1)
      continue;

logger << "Processing input";

    safe.lock();

    bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

    logger << "Processed keyboard";

    sf::Vector2f diff = getDiff(up, down, left, right);
    if (up != prevUp || down != prevDown || left != prevLeft || right != prevRight)
    {
      move(diff);
      prevUp = up;
      prevDown = down;
      prevLeft = left;
      prevRight = right;
    }

    logger << "Processing mouse";

    bool clicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    if (clicked != prevClicked) {
      fire(clicked);
      prevClicked = clicked;
    }

    sf::Vector2i posI = sf::Mouse::getPosition(*window);
    sf::Vector2f pos = sf::Vector2f(posI.x, posI.y);
    pos -= sf::Vector2f(getWindowHeigth(), getWindowWidth());
    rotate(pos);

    logger << "Processed mouse";

    safe.unlock();

    std::chrono::milliseconds tm(30);
    std::this_thread::sleep_for(tm);
  }
  std::chrono::milliseconds tm(300);
  std::this_thread::sleep_for(tm);
  }
}

void ClientView::shutdown()
{
  alive = false;
}

void ClientView::wake()
{
    alive = true;
}

}}} // namespace junk::client::view

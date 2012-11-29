#include "ClientView.hpp"

#include "game_object/GameObject.hpp"
#include "game_object/unit/Unit.hpp"
#include "game_object/unit/player/Player.hpp"

namespace junk {
namespace client {
namespace view {

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

//#KoCTblJIb

ClientView::ClientView()
: logger("CLIENT_VIEW", "client_view.log", true), clientId(-1)
, inputThread(&ClientView::processInput, this), alive(false)
{

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
}

void ClientView::update()
{
  removeObsoleteGameObjects();
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
    if (gameObject.second->destroyInfo.isDestroyed)
    {
      logger << "destroyCountdown " + std::to_string(gameObject.second->destroyInfo.destroyCountdown);

      if (gameObject.second->destroyInfo.destroyCountdown == 0)
      {
        destroyCandidates.push_back(gameObject.first);
      }
      else
      {
        gameObject.second->destroyInfo.destroyCountdown--;
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

void ClientView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  for (auto& gameObject : gameObjects)
  {
    target.draw(*gameObject.second, states);
  }
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

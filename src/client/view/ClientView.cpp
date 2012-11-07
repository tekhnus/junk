#include "ClientView.hpp"



namespace junk
{

sf::Vector2f getDiff(float time, bool up, bool down, bool left, bool right)
{
  time = 1;
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
: logger("CLIENT_VIEW", "client_view.log", true), clientID(-1)
, inputThread(&ClientView::processInput, this)
{

}

ClientView::~ClientView()
{
}

void ClientView::setModel(ClientModel* clientModel)
{
  makeActionSignal.connect(boost::bind(&ClientModel::makeAction, clientModel, _1));

  clientModel->gotClientIdSignal.connect(boost::bind(&ClientView::setClientID, this, _1));
  clientModel->clientAddedSignal.connect(boost::bind(&ClientView::addPlayer, this, _1, _2, _3));
  clientModel->clientPositionUpdatedSignal.connect(boost::bind(&ClientView::setPlayerPosition, this, _1, _2));
  clientModel->clientDirectionUpdatedSignal.connect(boost::bind(&ClientView::setPlayerRotation, this, _1, _2));
}

void ClientView::addPlayer(IDType playerID, sf::Vector2f position, sf::Vector2f rotation)
{
  logger << std::string("Adding player ") + std::to_string(playerID);
  assert(players.find(playerID) == players.end());
  players[playerID] = PlayerUnit(std::to_string(playerID), position, rotation);
}

void ClientView::removePlayer(IDType playerID)
{
  players.erase(playerID);
}

void ClientView::setPlayerPosition(IDType playerID, sf::Vector2f position)
{
  logger << std::string("setPlayerPosition invoked, id = ") + std::to_string(playerID);
  if (players.find(playerID) != players.end())
  {
    players[playerID].setPosition(position);
  }
}

void ClientView::setPlayerRotation(IDType playerID, sf::Vector2f rotation)
{
  logger << std::string("setPlayerRotation invoked, id = ") + std::to_string(playerID);
  if (players.find(playerID) != players.end())
  {
    players[playerID].setRotation(rotation);
  }
}

void ClientView::makeAction(const Action& action)
{
  logger << "makeAction invoked";
  makeActionSignal(action);
}

void ClientView::move(sf::Vector2f direction)
{
  logger << "move invoked";

  Action action;
  action.actionType = ActionType::MOVE;
  action.moveAction.direction.x = direction.x;
  action.moveAction.direction.y = direction.y;

  makeAction(action);
}

void ClientView::rotate(sf::Vector2f direction)
{
  logger << "rotate invoked";

  Action action;
  action.actionType = ActionType::ROTATE;
  action.rotateAction.direction.x = direction.x;
  action.rotateAction.direction.y = direction.y;

  makeAction(action);
}

void ClientView::setClientID(IDType clientID)
{
  logger << std::string("Setting client id to ") + std::to_string(clientID);
  this->clientID = clientID;
}

void ClientView::update()
{
  for (auto& player : players)
  {
    player.second.update();
  }
}

void ClientView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  for (auto& player : players)
  {
    target.draw(player.second, states);
  }
}

void ClientView::processInput()
{
  logger << "processInput thread started";
  return;
  while (true)
  {
    bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

    sf::Vector2f diff = getDiff(1.0, up, down, left, right);
    if (up != prevUp || down != prevDown || left != prevLeft || right != prevRight)
    {
      move(diff);
      prevUp = up;
      prevDown = down;
      prevLeft = left;
      prevRight = right;
    }
    if (players.find(clientID) != players.end())
      //if(clientID != -1)
    {
      sf::Vector2i posI = sf::Mouse::getPosition();
      sf::Vector2f pos = sf::Vector2f(posI.x, posI.y);
      sf::Vector2f player = players.at(clientID).getPosition();
      sf::Vector2f rot = player - pos;
      logger << rot.x << rot.y;
      //rotate(sf::Vector2f(-1,-1));
    }
    std::chrono::milliseconds tm(30);
    std::this_thread::sleep_for(tm);
  }
}

}

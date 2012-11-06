#include <SFML/System.hpp>
#include "ServerModel.hpp"

namespace junk
{

ServerModel::ServerModel() : logger("SERVER_MODEL", "server_model.log", true)
{
  networkModel.connectSignal.connect(boost::bind(&ServerModel::connectHandler, this));
  networkModel.getChangesSignal.connect(boost::bind(&ServerModel::getChangesHandler, this, _1));
  networkModel.moveSignal.connect(boost::bind(&ServerModel::moveHandler, this, _1, _2));
  networkModel.rotateSignal.connect(boost::bind(&ServerModel::rotateHandler, this, _1, _2));
  networkModel.fireSignal.connect(boost::bind(&ServerModel::fireHandler, this, _1, _2));

  logger << "ServerModel created";
}

ServerModel::~ServerModel()
{
  logger << "ServerModel destroyed";
}

void ServerModel::start()
{
  gameModel.start();
}

int32_t ServerModel::connectHandler()
{
  return gameModel.addPlayer();
}

GameChanges ServerModel::getChangesHandler(int32_t id)
{
  return gameModel.getChanges(id);
}

void ServerModel::moveHandler(int32_t id, sf::Vector2f direction)
{
  gameModel.move(id, direction);
}

void ServerModel::rotateHandler(int32_t id, sf::Vector2f direction)
{
  gameModel.rotate(id, direction);
}

void ServerModel::fireHandler(int32_t id, sf::Vector2f direction)
{
  //gameModel.fire(id, position);
}

} // namespace junk

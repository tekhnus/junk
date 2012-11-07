#include "ClientModel.hpp"

namespace junk
{

ClientModel::ClientModel() : logger("CLIENT_MODEL", "client_model.log", true)
{
  logger << "ClientModel created";
}

ClientModel::~ClientModel()
{
  logger << "ClientModel destructed";
}

int32_t ClientModel::connectToServer(const std::string& serverIp, int port)
{
  clientInfo.id = networkModel.connectToServer(serverIp, port);
  gotClientIdSignal(clientInfo.id);
  return clientInfo.id;
}

void ClientModel::update()
{
  logger << "update";
  GameChanges gameChanges = networkModel.getGameChanges();
  for (auto& patch : gameChanges.patches)
  {
    switch (patch.modelPatchType)
    {
      case ModelPatchType::MODEL_UNIT_PATCH:
        break;
    }
  }
}

void ClientModel::addPlayer(int32_t id, sf::Vector2f position, sf::Vector2f direction)
{
  logger << "Adding new player";
  players[id] = Player(id, position, direction);
  clientAddedSignal(id, position, direction);
}

void ClientModel::updatePlayerPosition(int32_t id, sf::Vector2f position)
{
  logger << "Updating player position";
  if (players.find(id) == players.end())
  {
    addPlayer(id, position, sf::Vector2f(1.0, 1.0));
  }
  else
  {
    players[id].setPosition(position);
    clientPositionUpdatedSignal(id, position);
    return;
  }
}

void ClientModel::updatePlayerDirection(int32_t id, sf::Vector2f direction)
{
  logger << "Updating player direction";
  if (players.find(id) == players.end())
  {
    addPlayer(id, sf::Vector2f(1.0, 1.0), direction);
  }
  else
  {
    players[id].setDirection(direction);
    clientDirectionUpdatedSignal(id, direction);
    return;
  }
}

void ClientModel::makeAction(const Action& action)
{
  networkModel.makeAction(action);
}

} // namespace junk

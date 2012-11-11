#include "ClientModel.hpp"

namespace junk {
namespace client {
namespace model {

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
    if (gameObjects.find(patch.id) == gameObjects.end())
    {
      addGameObject(patch);
    }
    gameObjects[patch.id]->applyPatch(patch);
  }
}

void ClientModel::addGameObject(const Patch& patch)
{
  logger << "Adding new GameObject";

  gameObjects.insert(std::make_pair(patch.id,
    std::unique_ptr<GameObject> (gameObjectFactory.create(patch.gameObjectType))));
  gameObjectAddedSignal(patch.gameObjectType, gameObjects[patch.id].get());
}

void ClientModel::makeAction(const Action& action)
{
  networkModel.makeAction(action);
}

}}} // namespace junk::client::model

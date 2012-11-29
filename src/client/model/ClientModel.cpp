#include "ClientModel.hpp"
#include "game_object/unit/Unit.hpp"
#include "game_object/unit/player/Player.hpp"

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

  logger << std::to_string(gameChanges.patches.size()) + " patches";

  for (auto& patch : gameChanges.patches)
  {
    logger << "patch received " + std::to_string(patch.id);
    if (gameObjects.find(patch.id) == gameObjects.end())
    {
      addGameObject(patch);
    }
    gameObjects[patch.id]->applyPatch(patch);
  }

  removeObsoleteGameObjects();
}

void ClientModel::removeObsoleteGameObjects()
{
  std::vector<int32_t> destroyCandidates;
  for (auto& gameObject : gameObjects)
  {
    if (gameObject.second->destroyInfo.isDestroyed)
    {
      logger << "destroyCountdown " + std::to_string(gameObject.second->destroyInfo.destroyCountdown);

      if (gameObject.second->destroyInfo.destroyCountdown == 0)
      {
        destroyCandidates.push_back(gameObject.second->id);
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

void ClientModel::addGameObject(const Patch& patch)
{
  logger << "Adding new GameObject " + std::to_string(patch.id);

  gameObjects.insert(std::make_pair(patch.id,
    std::unique_ptr<GameObject> (gameObjectFactory.create(patch.gameObjectType))));

  gameObjects[patch.id]->id = patch.id;

  gameObjectAddedSignal(patch.gameObjectType, gameObjects[patch.id].get());
}

void ClientModel::removeGameObject(int32_t id)
{
  if (gameObjects.find(id) == gameObjects.end())
  {
    logger << std::string("There is no such game object, id = ") + std::to_string(id);
  }
  else
  {
    gameObjects.erase(id);
    logger << "Game object removed, id = " + std::to_string(id);
  }
}

void ClientModel::makeAction(const Action& action)
{
  logger << "makeAction invoked";
  networkModel.makeAction(action);
}

}}} // namespace junk::client::model

#include <SFML/System.hpp>
#include "ServerModel.hpp"

namespace junk {
namespace server {
namespace model {

ServerModel::ServerModel() : logger("SERVER_MODEL", "server_model.log", true)
{
  networkModel.connectSignal.connect(boost::bind(&ServerModel::connectHandler, this, _1));
  networkModel.getChangesSignal.connect(boost::bind(&ServerModel::getChangesHandler, this, _1));
  networkModel.makeActionSignal.connect(boost::bind(&ServerModel::makeActionHandler, this, _1, _2));

  random.seed(42);
  sessionExpirationTime = sf::seconds(5.0f);

  logger << "ServerModel created";
}

ServerModel::~ServerModel()
{
  logger << "ServerModel destroyed";
}

void ServerModel::expiredSessionsCleaner()
{
  while (serverIsRunning)
  {
    clientInfoMutex.lock();

    logger << "Cleaning expired sessions";

    sf::Time currentTime = clock.getElapsedTime();

    std::vector<int32_t> eraseCandidates;
    for (const auto& it : clientInfo)
    {
      if (currentTime - it.second.lastUpdateTime > sessionExpirationTime)
      {
        eraseCandidates.push_back(it.first);
      }
    }
    for (auto index : eraseCandidates)
    {
      logger << std::string("Cleaning ") + std::to_string(index);
      clientInfo.erase(index);
    }

    clientInfoMutex.unlock();

    std::this_thread::sleep_for(std::chrono::seconds(5));
  }
}

void ServerModel::start()
{
  serverIsRunning = true;

  gameModel.start();

  expiredSessionsCleanerThread = std::shared_ptr<std::thread>
      (new std::thread(&ServerModel::expiredSessionsCleaner, this));

  clock.restart();
}

SessionInfo ServerModel::addClient(int32_t id)
{
  clientInfoMutex.lock();

  ClientInfo client(id);
  client.uuid = generator();
  client.lastUpdateTime = clock.getElapsedTime();
  clientInfo.insert(std::make_pair(id, client));

  SessionInfo sessionInfo;
  sessionInfo.id = client.id;
  sessionInfo.uuid = boost::uuids::to_string(client.uuid);

  clientInfoMutex.unlock();

  return sessionInfo;
}

void ServerModel::updateLastUpdateTime(int32_t id)
{
  clientInfo[id].lastUpdateTime = clock.getElapsedTime();
}

ServerModel::CheckStatus ServerModel::checkClientSessionInfo(const SessionInfo& sessionInfo)
{
  clientInfoMutex.lock();

  ServerModel::CheckStatus checkStatus;

  if (clientInfo.find(sessionInfo.id) == clientInfo.end())
  {
    checkStatus = ServerModel::CheckStatus::CLIENT_NOT_FOUND;
  }
  else
  if (boost::uuids::to_string(clientInfo[sessionInfo.id].uuid) != sessionInfo.uuid)
  {
    checkStatus = ServerModel::CheckStatus::WROND_UUID;
  }
  else
  {
    checkStatus = ServerModel::CheckStatus::CORRECT_UUID;
  }

  clientInfoMutex.unlock();

  return checkStatus;
}

SessionInfo ServerModel::connectHandler(const ConnectInfo& connectInfo)
{
  int playerID = gameModel.addPlayer(new Player());
  return addClient(playerID);
}

GameChanges ServerModel::getChangesHandler(const SessionInfo& sessionInfo)
{
  if (checkClientSessionInfo(sessionInfo) != ServerModel::CheckStatus::CORRECT_UUID)
  {
    throw BadLogin();
  }

  updateLastUpdateTime(sessionInfo.id);

  return gameModel.getChanges(sessionInfo.id);
}

void ServerModel::makeActionHandler(const SessionInfo& sessionInfo, const Action& action)
{
  if (checkClientSessionInfo(sessionInfo) != ServerModel::CheckStatus::CORRECT_UUID)
  {
    throw BadLogin();
  }

  updateLastUpdateTime(sessionInfo.id);
  gameModel.makeAction(action);
}

}}} // namespace junk::server::model

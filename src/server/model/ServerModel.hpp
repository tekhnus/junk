#pragma once

#include <unordered_map>
#include <thread>
#include <chrono>
#include <mutex>

#include <SFML/System.hpp>
#include <common/logger/Logger.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/random/mersenne_twister.hpp>

#include "network_model/ServerNetworkModel.hpp"
#include "game_model/ServerGameModel.hpp"


namespace junk
{

class ServerModel
{
public:
  ServerModel();
  ~ServerModel();

  void start();

private:
  GameChanges getChangesHandler(const SessionInfo &sessionInfo);
  SessionInfo connectHandler(const ConnectInfo& connectInfo);
  void makeActionHandler(const SessionInfo &sessionInfo, const Action& action);

  struct ClientInfo
  {
    ClientInfo(int32_t id = -1): id(id) {}

    int32_t id;
    boost::uuids::uuid uuid;
    sf::Time lastUpdateTime;
  };

  boost::mt19937 random;
  boost::uuids::basic_random_generator<boost::mt19937> generator;

  SessionInfo addClient(int32_t id);
  void updateLastUpdateTime(int32_t id);

  enum class CheckStatus
  {
    CLIENT_NOT_FOUND,
    WROND_UUID,
    CORRECT_UUID
  };

  CheckStatus checkClientSessionInfo(const SessionInfo& sessionInfo);

  std::unordered_map<int32_t, ClientInfo> clientInfo;

  ServerNetworkModel networkModel;
  ServerGameModel gameModel;

  sf::Clock clock;
  sf::Time sessionExpirationTime;

  bool serverIsRunning;

  void expiredSessionsCleaner();

  std::shared_ptr<std::thread> expiredSessionsCleanerThread;
  std::mutex clientInfoMutex;

  Logger logger;

}; // ServerModel

} // namespace junk

#pragma once

#include <SFML/System.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <common/logger/Logger.hpp>
#include <mutex>
#include <thread>
#include <unordered_map>

#include "game_model/ServerGameModel.hpp"
#include "network_model/ServerNetworkModel.hpp"

namespace junk {
namespace server {
namespace model {

// class CollisionHandler;

class ServerModel {
 public:
  ServerModel();
  ~ServerModel();

  void start();
  void join();

 private:
  GameChanges getChangesHandler(const SessionInfo& sessionInfo);
  SessionInfo connectHandler(const ConnectInfo& connectInfo);
  void makeActionHandler(const SessionInfo& sessionInfo, const Action& action);

  struct ClientInfo {
    explicit ClientInfo(int32_t id = -1) : id(id) {}

    int32_t id;
    boost::uuids::uuid uuid;
    sf::Time lastUpdateTime;
  };

  boost::mt19937 random;
  boost::uuids::basic_random_generator<boost::mt19937> generator;

  SessionInfo addClient(int32_t id);
  void updateLastUpdateTime(int32_t id);

  enum class CheckStatus { CLIENT_NOT_FOUND, WROND_UUID, CORRECT_UUID };

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
  CollisionHandler handler;

  Logger logger;

};  // ServerModel

}  // namespace model
}  // namespace server
}  // namespace junk

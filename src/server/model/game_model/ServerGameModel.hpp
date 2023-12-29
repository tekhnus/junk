#pragma once

#include <common/logger/Logger.hpp>
#include <gen-cpp/ClientService.h>

#include <unordered_map>
#include <thread>
#include <mutex>
#include <chrono>
#include <queue>
#include <box2d/box2d.h>

#include "game_object/GameObject.hpp"
#include "game_object/unit/player/Player.hpp"

#include "CollisionHandler.hpp"

namespace junk {
namespace server {
namespace model { 

class CollisionHandler;

class ServerGameModel
{
public:
  ServerGameModel();
  ~ServerGameModel();

  void start();
  void join();
  void stop();

  int32_t addPlayer(Player* player);

  void processGameObjectAddQueue();
  int32_t addGameObject(GameObject* gameObject);

  void removeObsoleteGameObjects();
  void removeGameObject(int32_t id);

  void removePlayer(int32_t playerId);
  void makeAction(const Action& action);

  GameChanges getChanges(int32_t id);

  void operator()();

  void loadMap(std::string filename);

  b2World* world;
  std::map<std::string, int> scoreBoard;

private:
  std::unordered_map<int32_t, std::unique_ptr<GameObject > > gameObjects;
  std::queue<GameObject*> gameObjectAddQueue;

  struct PlayerInfo
  {
    PlayerInfo()
    {
      lastUpdatedTime = std::chrono::high_resolution_clock::time_point();
    }

    std::chrono::high_resolution_clock::time_point lastUpdatedTime;
  };

  std::unordered_map<int32_t, PlayerInfo> playerInfo;

  int32_t firstFreeId;
  bool isRunning;
  sf::Clock gameLoopTimer;

  std::thread gameLoopThread;
  std::mutex gameChangesMutex;
  std::mutex gameObjectAddMutex;

  Logger logger;

  std::unique_ptr<CollisionHandler> handler;

  std::chrono::high_resolution_clock::time_point currentTime;
};

}}} // namespace junk::server::model

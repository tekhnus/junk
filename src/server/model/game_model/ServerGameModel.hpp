#pragma once

#include "SFML/System.hpp"
#include <common/logger/Logger.hpp>
#include <gen-cpp/ClientService.h>

#include <map>
#include <thread>
#include <mutex>
#include <chrono>
#include <Box2D/Box2D.h>

#include "game_object/GameObject.hpp"
#include "game_object/unit/player/Player.hpp"
#include "game_object/unit/bullet/Bullet.hpp"

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
  void stop();

  int32_t addPlayer(Player* player);

  int32_t addGameObject(GameObject* gameObject);

  void removeObsoleteGameObjects();
  void removeGameObject(int32_t id);

  void removePlayer(int32_t playerId);
  void makeAction(const Action& action);

  GameChanges getChanges(int32_t id);

  void operator()();

  b2World* world;

private:
  std::map<int32_t, std::unique_ptr<GameObject > > gameObjects;

  int32_t firstFreeId;
  bool isRunning;
  sf::Clock gameLoopTimer;

  std::thread gameLoopThread;
  std::mutex gameChangesMutex;

  Logger logger;

  std::unique_ptr<CollisionHandler> handler;

  std::chrono::high_resolution_clock::time_point currentTime;
};

}}} // namespace junk::server::model

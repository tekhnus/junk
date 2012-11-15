#pragma once

#include "SFML/System.hpp"
#include "Unit.hpp"
#include <common/logger/Logger.hpp>
#include <gen-cpp/ClientService.h>
#include <map>
#include <thread>
#include <mutex>
#include <Box2D.h>

#include "game_object/GameObject.hpp"
#include "game_object/unit/player/Player.hpp"

namespace junk {
namespace server {
namespace model {

class ServerGameModel
{
public:
  ServerGameModel();
  ~ServerGameModel();

  void start();
  void stop();

  int32_t addPlayer(Player* player);

  void removePlayer(int32_t playerId);
  void makeAction(const Action& action);

  GameChanges getChanges(int32_t id);

  void operator()();

private:
  std::map<int32_t, std::unique_ptr<GameObject > > gameObjects;

  void move(Player* player, const MoveAction& moveAction);
  void rotate(Player* player, const RotateAction& rotateAction);
  void fire(Player* player, const FireAction& fireAction);

  int32_t firstFreeId;
  bool isRunning;
  sf::Clock gameLoopTimer;

  std::thread gameLoopThread;
  std::mutex gameChangesMutex;

  Logger logger;
  b2World* world;
};

}}} // namespace junk::server::model

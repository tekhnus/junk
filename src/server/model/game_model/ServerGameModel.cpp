#include "ServerGameModel.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <functional>

#include "common/utils/Resource.hpp"
#include "server/model/game_model/game_object/unit/bonus/Bonus.hpp"
#include "server/model/game_model/game_object/unit/wall/Wall.hpp"

using boost::property_tree::ptree;

namespace junk {
namespace server {
namespace model {

ServerGameModel::ServerGameModel()
    : isRunning(false),
      logger("SERVER_GAME_MODEL", "server_model.log", true),
      handler(new CollisionHandler()) {
  world = new b2World(b2Vec2(0, 0));
  world->SetAllowSleeping(true);
  world->SetContactListener(handler.get());

  logger << "ServerGameModel created";
  firstFreeId = 0;
}

ServerGameModel::~ServerGameModel() {
  logger << "ServerGameModel destroyed";
  delete world;
}

void ServerGameModel::start() {
  isRunning = true;
  loadMap(get_resource_path("map.json"));
  gameLoopTimer.restart();
  gameLoopThread = std::thread(std::ref(*this));

  logger << "Game model started";
}

void ServerGameModel::join() {
  gameLoopThread.join();
}

void ServerGameModel::stop() {
  gameChangesMutex.lock();
  isRunning = false;
  gameChangesMutex.unlock();

  join();

  logger << "Game model stopped";
}

int32_t ServerGameModel::addPlayer(Player* player) {
  std::lock_guard<std::mutex> guard(gameChangesMutex);

  logger << "Adding a player...";

  int playerId = addGameObject(player);
  playerInfo.insert(std::make_pair(playerId, PlayerInfo()));

  if (scoreBoard.find(player->getName()) == scoreBoard.end()) {
    scoreBoard[player->getName()] = 0;
  }

  return playerId;
}

void ServerGameModel::processGameObjectAddQueue() {
  std::lock_guard<std::mutex> guard(gameObjectAddMutex);

  while (!gameObjectAddQueue.empty()) {
    GameObject* gameObject = gameObjectAddQueue.front();
    gameObjectAddQueue.pop();

    gameObjects.insert(std::make_pair(gameObject->id,
                                      std::unique_ptr<GameObject>(gameObject)));
  }
}

int32_t ServerGameModel::addGameObject(GameObject* gameObject) {
  std::lock_guard<std::mutex> guard(gameObjectAddMutex);

  logger << "Adding new object";
  int32_t newId = firstFreeId++;
  gameObject->id = newId;
  gameObject->model = this;
  gameObject->init();

  logger << std::string("New game object ID = ") + std::to_string(newId);

  gameObjectAddQueue.push(gameObject);

  return newId;
}

void ServerGameModel::removeObsoleteGameObjects() {
  std::vector<int32_t> destroyCandidates;

  for (auto& gameObject : gameObjects) {
    if (gameObject.second->destroyInfo.isDestructing) {
      if (gameObject.second->isDestroyed()) {
        gameObject.second->destroy();
      }
      if (gameObject.second->cleanupTime <= currentTime) {
        destroyCandidates.push_back(gameObject.second->id);
      }
    }
  }

  for (int32_t destroyCandidateId : destroyCandidates) {
    logger << "removing object, id = " + std::to_string(destroyCandidateId);

    gameObjects[destroyCandidateId]->destroy();
    gameObjects.erase(destroyCandidateId);
    playerInfo.erase(destroyCandidateId);
  }
}

void ServerGameModel::removeGameObject(int32_t id) {
  if (gameObjects.find(id) == gameObjects.end()) {
    logger << std::string("There is no such game object, id = ") +
                  std::to_string(id);
  } else {
    gameObjects.erase(id);
    logger << "Game object removed, id = " + std::to_string(id);
  }
}

void ServerGameModel::removePlayer(int32_t playerId) {
  logger.debug("starting destruction of player, id = ", playerId);
  if (gameObjects.find(playerId) != gameObjects.end())
    gameObjects[playerId]->startDestruction();
}

void ServerGameModel::makeAction(const Action& action) {
  std::lock_guard<std::mutex> guard(gameChangesMutex);

  // I think we should check it in ServerModel, not here
  if (gameObjects.find(action.playerId) == gameObjects.end()) {
    logger << "There is no such player with id " +
                  std::to_string(action.playerId);
    return;
  }
  Player* player = dynamic_cast<Player*>(gameObjects[action.playerId].get());
  switch (action.actionType) {
    case ActionType::MOVE:
      player->move(action.moveAction);
      break;

    case ActionType::ROTATE:
      player->rotate(action.rotateAction);
      break;

    case ActionType::FIRE:
      player->fire(action.fireAction);
      break;
    case ActionType::CHANGE_SETTINGS:
      //      dbg.debug("Got change settings. Id = ", action.playerId, "
      //      pointer: ", player, " nick ", changeSettingsAction.names);
      player->changeSettings(action.changeSettingsAction);
      break;
  }
}

GameChanges ServerGameModel::getChanges(int32_t id) {
  std::lock_guard<std::mutex> guard(gameChangesMutex);

  GameChanges gameChanges;

  if (gameObjects.find(id) == gameObjects.end()) {
    return gameChanges;
  }
  Player* player = dynamic_cast<Player*>(gameObjects[id].get());

  auto& lastUpdatedTime = playerInfo[id].lastUpdatedTime;

  for (const auto& gameObject : gameObjects) {
    // int32_t gameObjectId = gameObject.first;

    // If needToShow(gameObject, player)
    if (lastUpdatedTime < gameObject.second->lastUpdateTime) {
      if (player) {
        if (!player->canSee(gameObject.second.get())) {
          continue;
        }
      }

      gameChanges.patches.push_back(gameObject.second->getPatch());
    }
  }
  lastUpdatedTime = currentTime;

  return gameChanges;
}

void ServerGameModel::operator()() {
  int bonusCreationTimer = 0;
  while (true) {
    {
      std::lock_guard<std::mutex> guard(gameChangesMutex);
      if (bonusCreationTimer == 60) {
        Bonus* bonus =
            new Bonus(world, sf::Vector2f(rand() % 120 - 60, rand() % 120 - 60),
                      rand() % 3);
        addGameObject(bonus);
        bonusCreationTimer = 0;
      } else {
        bonusCreationTimer++;
      }
    }

    {
      std::lock_guard<std::mutex> guard(gameChangesMutex);

      currentTime = std::chrono::high_resolution_clock::now();

      if (!isRunning) {
        break;
      }

      for (auto& gameObject : gameObjects) {
        if (!gameObject.second->isDestroyed()) {
          gameObject.second->process();
        }
      }

      world->Step(1.0 / 60, 6, 2);

      removeObsoleteGameObjects();
      processGameObjectAddQueue();
    }

    std::chrono::milliseconds tm(20);
    std::this_thread::sleep_for(tm);
  }

  return;
}

void ServerGameModel::loadMap(std::string filename) {
  logger.warn("loading map...");
  ptree tree;
  read_json(filename, tree);
  for (const auto& entry : tree.get_child("walls")) {
    logger.debug("adding a wall...");
    std::vector<b2Vec2> corners;
    for (const auto& point : entry.second) {
      float x = point.second.get<float>("x");
      float y = point.second.get<float>("y");
      logger.debug("point: (", x, "; ", y, ")");
      corners.push_back(b2Vec2(x, y));
    }
    Wall* wall = new Wall();
    wall->model = this;
    wall->setCorners(corners);
    addGameObject(wall);
  }
}

}  // namespace model
}  // namespace server
}  // namespace junk

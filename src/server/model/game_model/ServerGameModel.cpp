#include "ServerGameModel.hpp"
#include "common/utils/Convert.hpp"
#include <functional>
#include <math.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;

namespace junk {
namespace server {
namespace model {

ServerGameModel::ServerGameModel()
: logger("SERVER_GAME_MODEL", "server_model.log", true), isRunning(false),
  handler(new CollisionHandler())
{
  //world = new b2World(aabb, b2Vec2(0, 0), true);
  world = new b2World(b2Vec2(0, 0));
  world->SetAllowSleeping(true);
  world->SetContactListener(handler.get());

  // double size = 720.0f / 20;
  // for(int i = -1; i <= 1; ++i) {
  //   for (int j = -1; j <=1; ++j) {
  //     if (i*i+j*j!=1)
  //       continue;
  //     b2BodyDef bodyDef;
  //     bodyDef.position.Set(i * (size + 0.5f) + 0.5f, j * (size + 0.5f) + 0.5f);

  //     b2Body* body = world->CreateBody(&bodyDef);
  //     b2PolygonShape polyShape;
  //     polyShape.SetAsBox(size/2, size/2, b2Vec2(size/2, size/2), 0);

  //     b2FixtureDef fixtureDef;
  //     fixtureDef.shape = &polyShape;
  //     fixtureDef.restitution = 0.5f;

  //     body->CreateFixture(&fixtureDef);
  //   }
  // }

  logger << "ServerGameModel created";
  firstFreeId = 0;
}

ServerGameModel::~ServerGameModel()
{
  logger << "ServerGameModel destroyed";
  delete world;
}

void ServerGameModel::start()
{
  isRunning = true;
  loadMap("map.json");
  gameLoopTimer.restart();
  gameLoopThread = std::thread(std::ref(*this));

  logger << "Game model started";
}

void ServerGameModel::stop()
{
  gameChangesMutex.lock();
  isRunning = false;
  gameChangesMutex.unlock();

  gameLoopThread.join();

  logger << "Game model stopped";
}

int32_t ServerGameModel::addPlayer(Player* player)
{
  std::lock_guard<std::mutex> guard(gameChangesMutex);

  logger << "Adding a player...";

  int playerId = addGameObject(player);

  return playerId;
}

void ServerGameModel::processGameObjectAddQueue()
{
  std::lock_guard<std::mutex> guard(gameObjectAddMutex);

  while (!gameObjectAddQueue.empty())
  {
    GameObject* gameObject = gameObjectAddQueue.front();
    gameObjectAddQueue.pop();

    gameObjects.insert(std::make_pair(gameObject->id,
                      std::unique_ptr<GameObject>(gameObject)));
  }
}

int32_t ServerGameModel::addGameObject(GameObject *gameObject)
{
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

void ServerGameModel::removeObsoleteGameObjects()
{
  std::vector<int32_t> destroyCandidates;

  for (auto& gameObject : gameObjects)
  {
    if (gameObject.second->destroyInfo.isDestructing)
    {
      if (gameObject.second->isDestroyed())
      {
        gameObject.second->destroy();
      }
      if (gameObject.second->cleanupTime <= currentTime)
      {
        destroyCandidates.push_back(gameObject.second->id);
      }
    }
  }

  for (int32_t destroyCandidateId : destroyCandidates)
  {
    logger << "removing object, id = " + std::to_string(destroyCandidateId);

    gameObjects[destroyCandidateId]->destroy();
    gameObjects.erase(destroyCandidateId);
  }
}

void ServerGameModel::removeGameObject(int32_t id)
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

void ServerGameModel::removePlayer(int32_t playerId)
{
  logger.debug("starting destruction of player, id = ", playerId);
  if (gameObjects.find(playerId) != gameObjects.end())
    gameObjects[playerId]->startDestruction();
}

void ServerGameModel::makeAction(const Action& action)
{
  std::lock_guard<std::mutex> guard(gameChangesMutex);

  // I think we should check it in ServerModel, not here
  if (gameObjects.find(action.playerId) == gameObjects.end())
  {
    logger << "There is no such player with id " + std::to_string(action.playerId);
    return;
  }
  Player* player = dynamic_cast<Player*> (gameObjects[action.playerId].get());

  switch (action.actionType)
  {
    case ActionType::MOVE:
      player->move(action.moveAction);
      break;

    case ActionType::ROTATE:
      player->rotate(action.rotateAction);
      break;

    case ActionType::FIRE:
      player->fire(action.fireAction);
      break;
  }
}

GameChanges ServerGameModel::getChanges(int32_t id)
{
  std::lock_guard<std::mutex> guard(gameChangesMutex);

  GameChanges gameChanges;
  for (const auto& gameObject : gameObjects)
  {
    gameChanges.patches.push_back(gameObject.second->getPatch());
  }
  return gameChanges;
}

void ServerGameModel::operator()()
{
  while (true)
  {
    {
      std::lock_guard<std::mutex> guard(gameChangesMutex);

      currentTime = std::chrono::high_resolution_clock::now();


      if (!isRunning)
      {
        break;
      }

      for (auto& gameObject : gameObjects)
      {
        if (!gameObject.second->isDestroyed())
        {
          gameObject.second->process();
        }
      }

      world->Step(1.0/60, 6, 2);

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

}}} // namespace junk::server::model

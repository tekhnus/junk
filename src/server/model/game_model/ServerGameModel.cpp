#include "ServerGameModel.hpp"
#include "common/utils/Convert.hpp"
#include <functional>
#include <math.h>

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

  double size = 720.0f / 20;
  for(int i = -1; i <= 1; ++i) {
    for (int j = -1; j <=1; ++j) {
      if (i*i+j*j!=1)
        continue;
      b2BodyDef bodyDef;
      bodyDef.position.Set(i * (size + 0.5f) + 0.5f, j * (size + 0.5f) + 0.5f);

      b2Body* body = world->CreateBody(&bodyDef);
      b2PolygonShape polyShape;
      polyShape.SetAsBox(size/2, size/2, b2Vec2(size/2, size/2), 0);

      b2FixtureDef fixtureDef;
      fixtureDef.shape = &polyShape;
      fixtureDef.restitution = 0.5f;

      body->CreateFixture(&fixtureDef);
    }
  }

  /*b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(0.0f, -10.0f);
  b2Body* groundBody = world->CreateBody(&groundBodyDef);

  b2PolygonShape groundBox;

  groundBox.SetAsBox(1000, 1000);

  groundBody->CreateFixture(&groundBox, 0.0f);*/

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
  gameChangesMutex.lock();

  logger << "Adding a player...";

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(3.0f, 3.0f);

  b2Body* body = world->CreateBody(&bodyDef);

  b2CircleShape circleShape;
  circleShape.m_radius = 1.0f;

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &circleShape;
  fixtureDef.density = 1.0f;
  fixtureDef.restitution = 0.5f;

  body->CreateFixture(&fixtureDef);
  body->SetLinearDamping(1.5);
  body->SetUserData((Unit*)player);

  player->body = body;
  player->force.SetZero();
  player->torque = 0.0f;

  int t = *((int*)(player->body->GetUserData()));
  dbg << "USER DATA: " + std::to_string(t);

  int playerId = addGameObject(player);

  gameChangesMutex.unlock();

  return playerId;
}

int32_t ServerGameModel::addGameObject(GameObject *gameObject)
{
  logger << "Adding new object";
  int32_t newId = firstFreeId++;
  gameObject->id = newId;
  gameObject->model = this;

  logger << std::string("New game object ID = ") + std::to_string(newId);

  gameObjects.insert(std::make_pair(newId,
                    std::unique_ptr<GameObject> (gameObject)));

  return newId;
}

void ServerGameModel::removeObsoleteGameObjects()
{
  gameChangesMutex.lock();

  std::vector<int32_t> destroyCandidates;
  for (auto& gameObject : gameObjects)
  {
    if (gameObject.second->destroyInfo.isDestroyed)
    {
      if (gameObject.second->destroyInfo.destroyCountdown == 0)
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

  gameChangesMutex.unlock();
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
      move(player, action.moveAction);
      break;

    case ActionType::ROTATE:
      rotate(player, action.rotateAction);
      break;

    case ActionType::FIRE:
      fire(player, action.fireAction);
      break;
  }
}

void ServerGameModel::move(Player* player, const MoveAction& moveAction)
{
  logger << "Move invoked";

  sf::Vector2f direction = common::to_SFML_Vector2f(moveAction.direction);
  direction = 100.0f* direction;

  b2Vec2 force(direction.x, direction.y);
  player->force = force;
}

void ServerGameModel::rotate(Player* player, const RotateAction& rotateAction)
{
  logger << "Rotate invoked " + std::to_string(rotateAction.direction.x) + " "
                              + std::to_string(rotateAction.direction.y);

  sf::Vector2f direction = common::to_SFML_Vector2f(rotateAction.direction);
  direction /= 20.0f;
  direction -= player->position;

  double DEGTORAD = M_PI / 180;
  double desiredAngle = atan2(direction.y, direction.x);
  double bodyAngle = player->body->GetAngle();
  float nextAngle = bodyAngle + player->body->GetAngularVelocity() / 10.0;
  float totalRotation = desiredAngle - nextAngle;

  while ( totalRotation < -180 * DEGTORAD ) totalRotation += 360 * DEGTORAD;
  while ( totalRotation >  180 * DEGTORAD ) totalRotation -= 360 * DEGTORAD;
  float desiredAngularVelocity = totalRotation * 10;
  float torque = player->body->GetInertia() * desiredAngularVelocity / (1/10.0);

  player->torque = torque;
}

void ServerGameModel::fire(Player* player, const FireAction& fireAction)
{
  player->fireOn = fireAction.on;
}

GameChanges ServerGameModel::getChanges(int32_t id)
{
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
    gameChangesMutex.lock();

    if (!isRunning)
    {
      gameChangesMutex.unlock();
      break;
    }

    for (auto& gameObject : gameObjects)
    {
      // logger.debug("Type is ", gameObject.second->getType());
      gameObject.second->process();
    }

    world->Step(1.0/60, 6, 2);

    gameChangesMutex.unlock();

    removeObsoleteGameObjects();

    std::chrono::milliseconds tm(20);
    std::this_thread::sleep_for(tm);
  }

  return;
}

}}} // namespace junk::server::model

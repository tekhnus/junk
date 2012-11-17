#include "ServerGameModel.hpp"
#include "common/utils/Convert.hpp"
#include <functional>
#include <math.h>

namespace junk {
namespace server {
namespace model {

ServerGameModel::ServerGameModel()
: logger("SERVER_GAME_MODEL", "server_model.log", true), isRunning(false)
{
  //world = new b2World(aabb, b2Vec2(0, 0), true);
  world = new b2World(b2Vec2(0, 0));
  world->SetAllowSleeping(true);

  int size = 25;
  for(int i = -1; i <= 1; ++i) {
    for (int j = -1; j <=1; ++j) {
      if (i*i+j*j!=1)
        continue;
      b2BodyDef bodyDef;
      bodyDef.position.Set(i * size, j * size);

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

  int32_t newPlayerId = firstFreeId++;

  logger << std::string("New player ID = ") + std::to_string(newPlayerId);

  player->id = newPlayerId;

  gameObjects.insert(std::make_pair(newPlayerId,
                    std::unique_ptr<GameObject> (player)));



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
  body->SetLinearDamping(0.99);

  player->body = body;
  player->force.SetZero();

  logger << "Player added";

  gameChangesMutex.unlock();

  return newPlayerId;
}

void ServerGameModel::removePlayer(int32_t playerId)
{
  gameChangesMutex.lock();

  logger << std::string("Removing a player with ID = ") + std::to_string(playerId);

  if (gameObjects.find(playerId) == gameObjects.end())
  {
    logger << std::string("There is no such player, id = ") + std::to_string(playerId);
  }
  else
  {
    gameObjects.erase(playerId);
    logger << "Player removed";
  }

  gameChangesMutex.unlock();
}

void ServerGameModel::makeAction(const Action& action)
{
  gameChangesMutex.lock();

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

  gameChangesMutex.unlock();
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
  direction -= player->position;

  double desiredAngle = atan2(direction.y, direction.x);
  double bodyAngle = player->body->GetAngle();
  double nextAngle = bodyAngle + player->body->GetAngularVelocity() / 2.0;
  double totalRotation = desiredAngle - nextAngle;

  float torque = totalRotation < 0 ? -10 : 10;

  /*
  double DEGTORAD = M_PI / 180;
  while ( totalRotation < -180 * DEGTORAD ) totalRotation += 360 * DEGTORAD;
  while ( totalRotation >  180 * DEGTORAD ) totalRotation -= 360 * DEGTORAD;
  float desiredAngularVelocity = totalRotation * 60;
  float torque = player->body->GetInertia() * desiredAngularVelocity / (1/60.0);
  */

  player->torque = torque;
}

void ServerGameModel::fire(Player* player, const FireAction& fireAction)
{
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
      gameObject.second->process();
    }

    world->Step(1.0/60, 6, 2);

    gameChangesMutex.unlock();
    std::chrono::milliseconds tm(20);
    std::this_thread::sleep_for(tm);
  }

  return;
}

}}} // namespace junk::server::model

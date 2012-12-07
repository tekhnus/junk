#include "GameObjectFactory.hpp"

#include "unit/player/Player.hpp"
#include "unit/bullet/Bullet.hpp"
#include "unit/bonus/Bonus.hpp"

namespace junk {
namespace client {
namespace view {

#define MODEL_GAME_OBJECT_REG( _Name, _name, _NAME) \
static bool view ## _Name ## _creator_registred = \
  GameObjectFactory::registerCreator<_Name>(GameObjectType::_NAME);

std::unordered_map<int, std::function<GameObject* ()> > GameObjectFactory::gameObjectCreator;
Logger GameObjectFactory::logger("VIEW_GAME_OBJECT_FACTORY", "client_model.log", true);

MODEL_GAME_OBJECT_REG(Player, player, PLAYER)
MODEL_GAME_OBJECT_REG(Bullet, bullet, BULLET)
MODEL_GAME_OBJECT_REG(Bonus, bonus, BONUS)

GameObjectFactory::GameObjectFactory()
{
  logger << "GameObjectFactory created";
}

GameObjectFactory::~GameObjectFactory()
{
  logger << "GameObjectFactory destructed";
}

GameObject* GameObjectFactory::create(const GameObjectType::type& gameObjectType)
{
  logger << "Creating new object of type " + std::to_string(gameObjectType);
  return gameObjectCreator[gameObjectType]();
}

}}} // namespace junk::client::view

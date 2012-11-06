#include "ClientServiceHandler.hpp"

namespace junk
{

ClientServiceHandler::ClientServiceHandler()
{
}

ClientServiceHandler::~ClientServiceHandler()
{
}

int32_t ClientServiceHandler::connect()
{
  return connectSignal();
}

void ClientServiceHandler::move(int32_t id, const Vector2f& direction)
{
  moveSignal(id, sf::Vector2f(direction.x, direction.y));
}

void ClientServiceHandler::rotate(int32_t id, const Vector2f& direction)
{
  rotateSignal(id, sf::Vector2f(direction.x, direction.y));
}

void ClientServiceHandler::fire(int32_t id, const Vector2f& direction)
{
  fireSignal(id, sf::Vector2f(direction.x, direction.y));
}

void ClientServiceHandler::getChanges(GameChanges& gameChanges, int32_t id)
{
  //getChangesMutex.lock();

  gameChanges = getChangesSignal(id);

  //getChangesMutex.unlock();
}

} // namespace junk

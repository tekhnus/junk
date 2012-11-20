#include "ClientServiceHandler.hpp"

#include <iostream>

namespace junk
{

ClientServiceHandler::ClientServiceHandler()
{
}

ClientServiceHandler::~ClientServiceHandler()
{
}

void ClientServiceHandler::connect(SessionInfo &sessionInfo, const ConnectInfo &connectInfo)
{
  serviceMutex.lock();

  sessionInfo = connectSignal(connectInfo);

  serviceMutex.unlock();
}

void ClientServiceHandler::makeAction(const SessionInfo &sessionInfo, const Action& action)
{
  std::cerr << "ACTION" << std::endl;
  std::cerr << action.moveAction.direction.x << " " << action.moveAction.direction.y << std::endl;
  makeActionSignal(sessionInfo, action);
}

void ClientServiceHandler::getChanges(GameChanges& gameChanges, const SessionInfo& sessionInfo)
{
  serviceMutex.lock();

  gameChanges = getChangesSignal(sessionInfo);

  serviceMutex.unlock();
}

} // namespace junk

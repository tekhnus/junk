#include "ClientServiceHandler.hpp"

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
  makeActionSignal(sessionInfo, action);
}

void ClientServiceHandler::getChanges(GameChanges& gameChanges, const SessionInfo& sessionInfo)
{
  serviceMutex.lock();

  gameChanges = getChangesSignal(sessionInfo);

  serviceMutex.unlock();
}

} // namespace junk

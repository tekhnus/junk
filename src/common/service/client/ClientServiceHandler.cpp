#include "ClientServiceHandler.hpp"

#include <common/logger/Logger.hpp>

namespace junk {

ClientServiceHandler::ClientServiceHandler() {}

ClientServiceHandler::~ClientServiceHandler() {}

void ClientServiceHandler::connect(SessionInfo& sessionInfo,
                                   const ConnectInfo& connectInfo) {
  std::lock_guard<std::mutex> lock(serviceMutex);

  sessionInfo = connectSignal(connectInfo);
}

void ClientServiceHandler::makeAction(const SessionInfo& sessionInfo,
                                      const Action& action) {
  std::lock_guard<std::mutex> lock(serviceMutex);

  makeActionSignal(sessionInfo, action);
}

void ClientServiceHandler::getChanges(GameChanges& gameChanges,
                                      const SessionInfo& sessionInfo) {
  std::lock_guard<std::mutex> lock(serviceMutex);

  gameChanges = getChangesSignal(sessionInfo);
}

}  // namespace junk

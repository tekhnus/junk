#pragma once

#include <SFML/System.hpp>
#include <boost/signals2.hpp>
#include <common/logger/Logger.hpp>

#include <gen-cpp/ClientService.h>

#include <mutex>

namespace junk
{

class ClientServiceHandler : virtual public ClientServiceIf
{
public:
  ClientServiceHandler();
  ~ClientServiceHandler();

  void connect(SessionInfo& sessionInfo, const ConnectInfo& connectInfo);

  void getChanges(GameChanges& gameChanges, const SessionInfo& sessionInfo);

  void makeAction(const SessionInfo& sessionInfo, const Action& action);

  boost::signals2::signal<SessionInfo (const ConnectInfo& connectInfo), boost::signals2::last_value<SessionInfo> > connectSignal;

  boost::signals2::signal<GameChanges (const SessionInfo& sessionInfo),
    boost::signals2::last_value<GameChanges> > getChangesSignal;

  boost::signals2::signal<void (const SessionInfo&, const Action& action)> makeActionSignal;

private:
  std::mutex serviceMutex;

}; // ClientServiceHandle

} // namespace junk

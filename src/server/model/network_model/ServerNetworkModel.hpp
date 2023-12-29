#pragma once

#include <SFML/System.hpp>
#include <common/logger/Logger.hpp>
#include <common/service/client/ClientServiceHandler.hpp>

#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/ThreadFactory.h>
#include <thrift/protocol/TCompactProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TNonblockingServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <thread>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;
using namespace apache::thrift::concurrency;

namespace junk
{

class ServerNetworkModel
{
public:
  ServerNetworkModel();
  ~ServerNetworkModel();

  boost::signals2::signal<SessionInfo (const ConnectInfo&),
    boost::signals2::last_value<SessionInfo> > connectSignal;

  boost::signals2::signal<GameChanges (const SessionInfo&), boost::signals2::last_value<GameChanges> > getChangesSignal;

  boost::signals2::signal<void (const SessionInfo&, const Action& action)> makeActionSignal;

private:

  // Client
  std::shared_ptr<ClientServiceHandler> handler;
  std::shared_ptr<TProcessor> processor;
  std::shared_ptr<TProtocolFactory> protocolFactory;
  std::shared_ptr<TNonblockingServerTransport > transport;
  std::shared_ptr<ThreadManager> threadManager;
  std::shared_ptr<ThreadFactory> threadFactory;
  std::shared_ptr<TNonblockingServer> server;

  std::shared_ptr<std::thread> serverThread;

  Logger logger;

}; // ServerNetworkModel

} // namespace junk

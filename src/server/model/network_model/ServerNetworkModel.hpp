#pragma once

#include <SFML/System.hpp>
#include <common/logger/Logger.hpp>
#include <common/service/client/ClientServiceHandler.hpp>

#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <unordered_map>
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

  int addClient();

  boost::signals2::signal<int32_t (), boost::signals2::last_value<int32_t> > connectSignal;
  boost::signals2::signal<GameChanges (int32_t), boost::signals2::last_value<GameChanges> > getChangesSignal;
  boost::signals2::signal<void (int32_t, sf::Vector2f)> moveSignal;
  boost::signals2::signal<void (int32_t, sf::Vector2f)> rotateSignal;
  boost::signals2::signal<void (int32_t, sf::Vector2f)> fireSignal;

private:

  // Client
  boost::shared_ptr<ClientServiceHandler> handler;
  boost::shared_ptr<TProcessor> processor;
  boost::shared_ptr<TProtocolFactory> protocolFactory;
  boost::shared_ptr<ThreadManager> threadManager;
  boost::shared_ptr<PosixThreadFactory> threadFactory;
  boost::shared_ptr<TNonblockingServer> server;

  std::shared_ptr<std::thread> serverThread;

  Logger logger;

}; // ServerNetworkModel

} // namespace junk

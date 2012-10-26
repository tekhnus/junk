#pragma once

#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
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

  void subscribeForConnectSignal(sigc::slot<int32_t> slot);
  void subscribeForGetChangesSignal(sigc::slot<GameChanges, int32_t> slot);
  void subscribeForMoveSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);
  void subscribeForRotateSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);
  void subscribeForFireSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);

private:
 
  // Client
  boost::shared_ptr<ClientServiceHandler> handler;
  boost::shared_ptr<TProcessor> processor;
  boost::shared_ptr<TProtocolFactory> protocolFactory;
  boost::shared_ptr<ThreadManager> threadManager;
  boost::shared_ptr<PosixThreadFactory> threadFactory;
  boost::shared_ptr<TNonblockingServer> server;

  /*boost::shared_ptr<TServerTransport> serverTransport;
  boost::shared_ptr<TTransportFactory> transportFactory;
  boost::shared_ptr<TProtocolFactory> protocolFactory;
  boost::shared_ptr<TThreadedServer> server;*/

  std::shared_ptr<std::thread> serverThread;

  Logger logger;
  
}; // ServerNetworkModel

} // namespace junk

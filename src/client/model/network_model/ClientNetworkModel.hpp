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
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

namespace junk
{

class ClientNetworkModel
{
public:
  ClientNetworkModel();
  ~ClientNetworkModel();

  void connectToServer(const std::string& serverIp, int port);

  void subscribeForPositionUpdatedSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);
  void subscribeForDirectionUpdatedSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);

  void move(sf::Vector2f direction);
  void fire(sf::Vector2f direction);
  void rotate(sf::Vector2f direction);

private:

  int32_t id;

	// Client
  boost::shared_ptr<TTransport> socket;
  boost::shared_ptr<TTransport> transport;
  boost::shared_ptr<TProtocol> protocol;
  boost::shared_ptr<ClientServiceClient> clientServiceClient;

  Logger logger;
  
}; // ClientNetworkModel

} // namespace junk

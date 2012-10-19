#pragma once

#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include <common/logger/Logger.hpp>
#include <common/service/server/ServerServiceHandler.hpp>
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

sf::Vector2f convert(const Vector2f& v)
{
  return sf::Vector2f(v.x, v.y);
}

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

  // Server
  boost::shared_ptr<ServerServiceHandler> handler;
  boost::shared_ptr<TProcessor> processor;
  boost::shared_ptr<TServerTransport> serverTransport;
  boost::shared_ptr<TTransportFactory> transportFactory;
  boost::shared_ptr<TProtocolFactory> protocolFactory;
  boost::shared_ptr<TSimpleServer> server;

  Logger logger;
  
}; // ClientNetworkModel

} // namespace junk

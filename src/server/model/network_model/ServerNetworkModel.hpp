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

#include <unordered_map>

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

class ServerNetworkModel
{
public:
  ServerNetworkModel();
  ~ServerNetworkModel();


  void subscribeForMoveSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);
  void subscribeForRotateSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);
  void subscribeForFireSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);

  void clientPositionUpdated(uint32_t id, sf::Vector2f direction);
  void clientDirectionUpdated(uint32_t id, sf::Vector2f direction);
  void fireUpdated();

private:

	// Server
  std::unordered_map< int32_t, boost::shared_ptr<TTransport> > socket;
  std::unordered_map< int32_t, boost::shared_ptr<TTransport> > transport;
  std::unordered_map< int32_t, boost::shared_ptr<TProtocol> > protocol;
  std::unordered_map< int32_t, boost::shared_ptr<ServerServiceClient> > serverServiceClient;

  // Client
  boost::shared_ptr<ClientServiceHandler> handler;
  boost::shared_ptr<TProcessor> processor;
  boost::shared_ptr<TServerTransport> serverTransport;
  boost::shared_ptr<TTransportFactory> transportFactory;
  boost::shared_ptr<TProtocolFactory> protocolFactory;
  boost::shared_ptr<TSimpleServer> server;

  Logger logger;
  
}; // ServerNetworkModel

} // namespace junk

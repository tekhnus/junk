#pragma once

#include <thrift/concurrency/ThreadManager.h>
#include <thrift/protocol/TCompactProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <SFML/System.hpp>
#include <boost/uuid/uuid.hpp>
#include <common/logger/Logger.hpp>
#include <common/service/client/ClientServiceHandler.hpp>

namespace junk {

class ClientNetworkModel {
 public:
  ClientNetworkModel();
  ~ClientNetworkModel();

  int32_t connectToServer(const std::string& serverIp, int port);

  GameChanges getGameChanges();
  void makeAction(const Action& action);

  void shutdown();

 private:
  SessionInfo sessionInfo;

  std::shared_ptr<apache::thrift::transport::TSocket> socket;
  std::shared_ptr<apache::thrift::protocol::TTransport> transport;
  std::shared_ptr<apache::thrift::protocol::TProtocol> protocol;
  std::shared_ptr<ClientServiceClient> clientServiceClient;

  std::mutex socketMutex;

  Logger logger;

  bool alive;

};  // ClientNetworkModel

}  // namespace junk

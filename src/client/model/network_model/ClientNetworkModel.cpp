#include "ClientNetworkModel.hpp"
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TBufferTransports.h>

namespace junk {

using apache::thrift::transport::TFramedTransport;
using apache::thrift::protocol::TProtocol;
using apache::thrift::protocol::TCompactProtocol;
using apache::thrift::transport::TSocket;
using apache::thrift::transport::TTransport;

ClientNetworkModel::ClientNetworkModel()
    : logger("CLIENT_NETWORK_MODEL", "client_model.log", true), alive(true) {
  logger << "ClientNetworkModel created";
}

int32_t ClientNetworkModel::connectToServer(const std::string& serverIp,
                                            int port) {
  logger.debug("Connecting to server");

  socket = std::shared_ptr<TSocket>(new TSocket(serverIp, port));
  transport = std::shared_ptr<TTransport>(new TFramedTransport(socket));
  protocol = std::shared_ptr<TProtocol>(new TCompactProtocol(transport));
  clientServiceClient =
      std::shared_ptr<ClientServiceClient>(new ClientServiceClient(protocol));

  transport->open();

  ConnectInfo connectInfo;
  clientServiceClient->connect(sessionInfo, connectInfo);

  logger.debug("Connected to server, id = ", sessionInfo.id);

  alive = true;

  return sessionInfo.id;
}

ClientNetworkModel::~ClientNetworkModel() {
  shutdown();
}

GameChanges ClientNetworkModel::getGameChanges() {
  std::lock_guard<std::mutex> lock(socketMutex);

  if (!alive) {
    return GameChanges();
  }

  logger << "Getting changes";

  GameChanges gameChanges;
  clientServiceClient->getChanges(gameChanges, sessionInfo);

  return gameChanges;
}

void ClientNetworkModel::makeAction(const Action& action) {
  std::lock_guard<std::mutex> lock(socketMutex);

  if (!alive) {
    return;
  }

  logger << "ClientNetworkModel::makeAction(), id = " +
                std::to_string(sessionInfo.id);
  try {
    clientServiceClient->makeAction(sessionInfo, action);
  } catch (apache::thrift::transport::TTransportException e) {
  }
}

void ClientNetworkModel::shutdown() {
  alive = false;
  if (transport != nullptr) {
    try {
      transport->close();
    }
    catch (...){
      logger << "Exception caught while closing transport";
    }
  }
  logger << "ClientNetworkModel shut down";
}

}  // namespace junk

#include "ServerNetworkModel.hpp"

namespace th = apache::thrift;
namespace se = apache::thrift::server;

namespace junk {

ServerNetworkModel::ServerNetworkModel()
    : logger("SERVER_NETWORK_MODEL", "server_model.log", true) {
  handler = std::shared_ptr<ClientServiceHandler>(new ClientServiceHandler());
  processor =
      std::shared_ptr<se::TProcessor>(new ClientServiceProcessor(handler));
  protocolFactory = std::shared_ptr<se::TProtocolFactory>(
      new th::protocol::TCompactProtocolFactory());
  transport = std::shared_ptr<se::TNonblockingServerTransport>(
      new th::transport::TNonblockingServerSocket(7777));
  // using thread pool with maximum 15 threads to handle incoming requests
  threadManager = std::shared_ptr<se::ThreadManager>(
      se::ThreadManager::newSimpleThreadManager(15));
  threadFactory = std::shared_ptr<se::ThreadFactory>(new se::ThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();
  server = std::shared_ptr<se::TNonblockingServer>(new se::TNonblockingServer(
      processor, protocolFactory, transport, threadManager));

  serverThread = std::shared_ptr<std::thread>(
      new std::thread(&se::TNonblockingServer::serve, server.get()));

  handler->connectSignal.connect(this->connectSignal);
  handler->getChangesSignal.connect(this->getChangesSignal);
  handler->makeActionSignal.connect(this->makeActionSignal);

  logger << "ServerNetworkModel created";
}

ServerNetworkModel::~ServerNetworkModel() {
  logger << "ServerNetworkModel destructed";
}

}  // namespace junk

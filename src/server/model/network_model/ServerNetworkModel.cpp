#include "ServerNetworkModel.hpp"

namespace junk {

ServerNetworkModel::ServerNetworkModel()
    : logger("SERVER_NETWORK_MODEL", "server_model.log", true) {
  handler = std::shared_ptr<ClientServiceHandler>(new ClientServiceHandler());
  processor = std::shared_ptr<TProcessor>(new ClientServiceProcessor(handler));
  protocolFactory =
      std::shared_ptr<TProtocolFactory>(new TCompactProtocolFactory());
  transport = std::shared_ptr<TNonblockingServerTransport>(
      new TNonblockingServerSocket(7777));
  // using thread pool with maximum 15 threads to handle incoming requests
  threadManager =
      std::shared_ptr<ThreadManager>(ThreadManager::newSimpleThreadManager(15));
  threadFactory = std::shared_ptr<ThreadFactory>(new ThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();
  server = std::shared_ptr<TNonblockingServer>(new TNonblockingServer(
      processor, protocolFactory, transport, threadManager));

  serverThread = std::shared_ptr<std::thread>(
      new std::thread(&TNonblockingServer::serve, server.get()));

  handler->connectSignal.connect(this->connectSignal);
  handler->getChangesSignal.connect(this->getChangesSignal);
  handler->makeActionSignal.connect(this->makeActionSignal);

  logger << "ServerNetworkModel created";
}

ServerNetworkModel::~ServerNetworkModel() {
  logger << "ServerNetworkModel destructed";
}

}  // namespace junk

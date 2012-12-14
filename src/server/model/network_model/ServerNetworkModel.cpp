#include "ServerNetworkModel.hpp"

namespace junk
{

ServerNetworkModel::ServerNetworkModel() : logger("SERVER_NETWORK_MODEL", "server_model.log", true)
{
  handler = boost::shared_ptr<ClientServiceHandler > (new ClientServiceHandler());
  processor = boost::shared_ptr<TProcessor > (new ClientServiceProcessor(handler));
  protocolFactory = boost::shared_ptr<TProtocolFactory > (new TCompactProtocolFactory());

  // using thread pool with maximum 15 threads to handle incoming requests
  threadManager = boost::shared_ptr<ThreadManager > (ThreadManager::newSimpleThreadManager(15));
  threadFactory = boost::shared_ptr<PosixThreadFactory > (new PosixThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();
  server = boost::shared_ptr<TNonblockingServer >
    (new TNonblockingServer(processor, protocolFactory, 7777, threadManager));

  serverThread = std::shared_ptr<std::thread >
    (new std::thread(&TNonblockingServer::serve, server.get()));

  handler->connectSignal.connect(this->connectSignal);
  handler->getChangesSignal.connect(this->getChangesSignal);
  handler->makeActionSignal.connect(this->makeActionSignal);

  logger << "ServerNetworkModel created";
}

ServerNetworkModel::~ServerNetworkModel()
{
  logger << "ServerNetworkModel destructed";
}

} // namespace junk

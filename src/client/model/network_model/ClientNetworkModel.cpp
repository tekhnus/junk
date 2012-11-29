#include "ClientNetworkModel.hpp"

namespace junk
{

ClientNetworkModel::ClientNetworkModel() : logger("CLIENT_NETWORK_MODEL", "client_model.log", true),
  alive(true)
{
  logger << "ClientNetworkModel created";
}

int32_t ClientNetworkModel::connectToServer(const std::string& serverIp, int port)
{
  logger << "Connecting to server";

  socket = boost::shared_ptr<TSocket > (new TSocket(serverIp, port));
  transport = boost::shared_ptr<TTransport > (new TFramedTransport(socket));
  protocol = boost::shared_ptr<TProtocol > (new TBinaryProtocol(transport));
  clientServiceClient = boost::shared_ptr<ClientServiceClient > (new ClientServiceClient(protocol));

  transport->open();

  ConnectInfo connectInfo;
  clientServiceClient->connect(sessionInfo, connectInfo);

  std::string message = "Connected to server, id = " + std::to_string(sessionInfo.id);
  logger << message;

  alive = true;
  
  return sessionInfo.id;
}

ClientNetworkModel::~ClientNetworkModel()
{
  shutdown();
}

GameChanges ClientNetworkModel::getGameChanges()
{
  if (!alive)
  {
    return GameChanges();
  }
  socketMutex.lock();
  logger << "Getting changes";

  GameChanges gameChanges;
  clientServiceClient->getChanges(gameChanges, sessionInfo);

  socketMutex.unlock();

  return gameChanges;
}

void ClientNetworkModel::makeAction(const Action& action)
{
  if (!alive)
  {
    return;
  }
  socketMutex.lock();

  logger << "ClientNetworkModel::makeAction(), id = " + std::to_string(sessionInfo.id);
  logger << action.moveAction.direction.x;
  logger << action.moveAction.direction.y;
  try {
  clientServiceClient->makeAction(sessionInfo, action);
  } catch(apache::thrift::transport::TTransportException e)
  {

  }

  socketMutex.unlock();
}

void ClientNetworkModel::shutdown()
{
  alive = false;
  transport->close();
  logger << "ClientNetworkModel shut down";
}

} // namespace junk

#include "ClientNetworkModel.hpp"

namespace junk
{

ClientNetworkModel::ClientNetworkModel() : logger("CLIENT_NETWORK_MODEL", "client_model.log", true)
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
  return sessionInfo.id;
}

ClientNetworkModel::~ClientNetworkModel()
{
  logger << "ClientNetworkModel destructed";
}

GameChanges ClientNetworkModel::getGameChanges()
{
  socketMutex.lock();
  logger << "Getting changes";

  GameChanges gameChanges;
  clientServiceClient->getChanges(gameChanges, sessionInfo);

  socketMutex.unlock();

  return gameChanges;
}

void ClientNetworkModel::makeAction(const Action& action)
{
  socketMutex.lock();

  logger << action.moveAction.direction.x;
  logger << action.moveAction.direction.y;
  clientServiceClient->makeAction(sessionInfo, action);

  socketMutex.unlock();
}

} // namespace junk

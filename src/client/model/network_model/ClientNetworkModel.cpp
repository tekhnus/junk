#include "ClientNetworkModel.hpp"

namespace junk
{

sf::Vector2f convert(const Vector2f& v)
{
  return sf::Vector2f(v.x, v.y);
}

ClientNetworkModel::ClientNetworkModel() : logger("CLIENT_NETWORK_MODEL", "client_model.log", true)
{
	logger << "ClientNetworkModel created";
}

int32_t ClientNetworkModel::connectToServer(const std::string& serverIp, int port)
{
  logger << "Connecting to server";

  socket = boost::shared_ptr<TSocket> (new TSocket(serverIp, port));
  transport = boost::shared_ptr<TTransport> (new TFramedTransport(socket));
  protocol = boost::shared_ptr<TProtocol> (new TBinaryProtocol(transport));
  clientServiceClient = boost::shared_ptr<ClientServiceClient> (new ClientServiceClient(protocol));

  transport->open();
  id = clientServiceClient->connect();

  std::string message = "Connected to server, id = " + std::to_string(id);
  logger << message;
  return id;
}

ClientNetworkModel::~ClientNetworkModel()
{
	logger << "ClientNetworkModel destructed";
}

GameChanges ClientNetworkModel::getGameChanges()
{
  socketMutex.lock();

  GameChanges gameChanges;
  clientServiceClient->getChanges(gameChanges, id);

  socketMutex.unlock();
  return gameChanges;
}

void ClientNetworkModel::move(sf::Vector2f direction_)
{
  socketMutex.lock();

  logger << std::string("move ") + std::to_string(direction_.x) + std::string(" ") + std::to_string(direction_.y);
  Vector2f direction;
  direction.x = direction_.x;
  direction.y = direction_.y;
  clientServiceClient->move(id, direction);

  socketMutex.unlock();
}

void ClientNetworkModel::rotate(sf::Vector2f direction_)
{
  socketMutex.lock();

  Vector2f direction;
  direction.x = direction_.x;
  direction.y = direction_.y;
  clientServiceClient->rotate(id, direction);

  socketMutex.unlock();
}

void ClientNetworkModel::fire(sf::Vector2f direction_)
{
  socketMutex.lock();

  Vector2f direction;
  direction.x = direction_.x;
  direction.y = direction_.y;
  clientServiceClient->fire(id, direction);

  socketMutex.unlock();
}

} // namespace junk
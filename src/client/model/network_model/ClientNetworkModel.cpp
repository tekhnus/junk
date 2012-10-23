#include "ClientNetworkModel.hpp"

namespace junk
{

sf::Vector2f convert(const Vector2f& v)
{
  return sf::Vector2f(v.x, v.y);
}

ClientNetworkModel::ClientNetworkModel() : logger("client_model.log", "CLIENT_NETWORK_MODEL", true)
{
	logger << "ClientNetworkModel created";
}

void ClientNetworkModel::connectToServer(const std::string& serverIp, int port)
{
  logger << "Connecting to server";

  socket = boost::shared_ptr<TSocket> (new TSocket(serverIp, port));
  transport = boost::shared_ptr<TTransport> (new TBufferedTransport(socket));
  protocol = boost::shared_ptr<TProtocol> (new TBinaryProtocol(transport));
  clientServiceClient = boost::shared_ptr<ClientServiceClient> (new ClientServiceClient(protocol));
  id = clientServiceClient->connect();

  logger << "Connected to server, id = " << std::to_string(id);
}

ClientNetworkModel::~ClientNetworkModel()
{
	logger << "ClientNetworkModel destructed";
}

GameChanges ClientNetworkModel::getGameChanges()
{
  GameChanges gameChanges;
  clientServiceClient->getChanges(gameChanges, id);
  return gameChanges;
}

void ClientNetworkModel::move(sf::Vector2f direction_)
{
  Vector2f direction;
  direction.x = direction_.x;
  direction.y = direction_.y;
  clientServiceClient->move(id, direction);
}

void ClientNetworkModel::rotate(sf::Vector2f direction_)
{
  Vector2f direction;
  direction.x = direction_.x;
  direction.y = direction_.y;
  clientServiceClient->rotate(id, direction);
}

void ClientNetworkModel::fire(sf::Vector2f direction_)
{
  Vector2f direction;
  direction.x = direction_.x;
  direction.y = direction_.y;
  clientServiceClient->fire(id, direction);
}

} // namespace junk
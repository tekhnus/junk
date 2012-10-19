#include "ServerNetworkModel.hpp"

namespace junk
{

ServerNetworkModel::ServerNetworkModel() : logger("server_model.log", "SERVER_NETWORK_MODEL", true)
{
  handler = boost::shared_ptr<ClientServiceHandler> (new ClientServiceHandler());
  processor = boost::shared_ptr<TProcessor> (new ServerServiceProcessor(handler));
  serverTransport = boost::shared_ptr<TServerTransport> (new TServerSocket(port));
  transportFactory = boost::shared_ptr<TTransportFactory> (new TBufferedTransportFactory());
  protocolFactory = boost::shared_ptr<TProtocolFactory> (new TBinaryProtocolFactory());

  server = boost::shared_ptr<TSimpleServer> 
  	(new TSimpleServer (processor, serverTransport, transportFactory, protocolFactory));
  server->serve();

	logger << "ServerNetworkModel created";
}

void ServerNetworkModel::addClient(const std::string& clientIp, int port)
{
  //clientServiceClient[lastID]->connected(lastId);
  lastID++;
}

ServerNetworkModel::~ServerNetworkModel()
{
	logger << "ServerNetworkModel destructed";
}

void ServerNetworkModel::subscribeForMoveSignal(sigc::slot<void, int32_t, sf::Vector2f> slot)
{
  handler->subscribeForMoveSignal(slot);
}

void ServerNetworkModel::subscribeForRotateSignal(sigc::slot<void, int32_t, sf::Vector2f> slot)
{
  handler->subscribeForRotateSignal(slot);
}

void ServerNetworkModel::subscribeForFireSignal(sigc::slot<void, int32_t, sf::Vector2f> slot)
{
  handler->subscribeForFireSignal(slot);
}

Vector2f convertSFMLtoThrift(sf::Vector2f v)
{
  Vector2f v1;
  v1.x = v.x;
  v1.y = v.y;
  return v1;
}

void ServerNetworkModel::clientPositionUpdated(uint32_t id, sf::Vector2f direction_)
{
  Vector2f direction = convertSFMLtoThrift(direction_);
  for (auto& service : serverServiceClient)
  {
    service.second->clientPositionUpdated(id, direction); // change to position
  }
}

void ServerNetworkModel::clientDirectionUpdated(uint32_t id, sf::Vector2f direction_)
{
  Vector2f direction = convertSFMLtoThrift(direction_);
  for (auto& service : serverServiceClient)
  {
    service.second->clientDirectionUpdated(id, direction);
  }
}

void ServerNetworkModel::fireUpdated()
{
  /*for (auto& service : serverServiceClient)
  {
    service->clientPositionUpdated(id, direction);
  }*/
}


} // namespace junk

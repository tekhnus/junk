#include "ServerNetworkModel.hpp"

namespace junk
{

ServerNetworkModel::ServerNetworkModel() : logger("server_model.log", "SERVER_NETWORK_MODEL", true)
{
  handler = boost::shared_ptr<ClientServiceHandler> (new ClientServiceHandler());
  processor = boost::shared_ptr<TProcessor> (new ClientServiceProcessor(handler));
  serverTransport = boost::shared_ptr<TServerTransport> (new TServerSocket(8099));
  transportFactory = boost::shared_ptr<TTransportFactory> (new TBufferedTransportFactory());
  protocolFactory = boost::shared_ptr<TProtocolFactory> (new TBinaryProtocolFactory());

  server = boost::shared_ptr<TSimpleServer> 
  	(new TSimpleServer (processor, serverTransport, transportFactory, protocolFactory));
  server->serve();

	logger << "ServerNetworkModel created";
}

ServerNetworkModel::~ServerNetworkModel()
{
	logger << "ServerNetworkModel destructed";
}

int ServerNetworkModel::addClient()
{
  return lastID++;
}

void ServerNetworkModel::subscribeForGetChangesSignal(sigc::slot<GameChanges, int32_t> slot)
{
  handler->subscribeForGetChangesSignal(slot);
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
}

void ServerNetworkModel::clientDirectionUpdated(uint32_t id, sf::Vector2f direction_)
{
}

void ServerNetworkModel::fireUpdated()
{
  /*for (auto& service : serverServiceClient)
  {
    service->clientPositionUpdated(id, direction);
  }*/
}


} // namespace junk

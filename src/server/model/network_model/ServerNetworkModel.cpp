#include "ServerNetworkModel.hpp"

namespace junk
{

sf::Vector2f convert(const Vector2f& v)
{
  return sf::Vector2f(v.x, v.y);
}

ServerNetworkModel::ServerNetworkModel() : logger("SERVER_NETWORK_MODELj", "server_model.log", true)
{
  handler = boost::shared_ptr<ClientServiceHandler> (new ClientServiceHandler());
  processor = boost::shared_ptr<TProcessor> (new ClientServiceProcessor(handler));
  serverTransport = boost::shared_ptr<TServerTransport> (new TServerSocket(7777));
  transportFactory = boost::shared_ptr<TTransportFactory> (new TBufferedTransportFactory());
  protocolFactory = boost::shared_ptr<TProtocolFactory> (new TBinaryProtocolFactory());

  server = boost::shared_ptr<TThreadedServer> 
  	(new TThreadedServer (processor, serverTransport, transportFactory, protocolFactory));

  serverThread = std::shared_ptr<std::thread> (new std::thread(&TThreadedServer::serve, server));

  //server->serve();

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

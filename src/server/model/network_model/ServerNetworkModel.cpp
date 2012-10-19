#include "ServerNetworkModel.hpp"

namespace junk
{

ServerNetworkModel::ServerNetworkModel() : logger("server_model.log", "SERVER_NETWORK_MODEL", true)
{
  /*handler = boost::shared_ptr<ClientServiceHandler> (new ClientServiceHandler());
  processor = boost::shared_ptr<TProcessor> (new ServerServiceProcessor(handler));
  serverTransport = boost::shared_ptr<TServerTransport> (new TServerSocket(port));
  transportFactory = boost::shared_ptr<TTransportFactory> (new TBufferedTransportFactory());
  protocolFactory = boost::shared_ptr<TProtocolFactory> (new TBinaryProtocolFactory());

  server = boost::shared_ptr<TSimpleServer> 
  	(new TSimpleServer (processor, serverTransport, transportFactory, protocolFactory));
  server->serve();

	logger << "ServerNetworkModel created";
*/}

/*
void ClientNetworkModel::connectToServer(const std::string& serverIp, int port)
{
  socket = boost::shared_ptr<TTransport> (new TSocket(serverIp, port));
  transport = boost::shared_ptr<TTransport> (new TBufferedTransport(socket));
  protocol = boost::shared_ptr<TProtocol> (new TBinaryProtocol(transport));
  clientServiceClient = boost::shared_ptr<ClientServiceClient> (new ClientServiceClient(protocol));
}
*/

ServerNetworkModel::~ServerNetworkModel()
{
	logger << "ServerNetworkModel destructed";
}

void ClientNetworkModel::subscribeForMoveSignal(sigc::slot<void, int32_t, sf::Vector2f> slot)
{
  handler->subscribeForMoveSignal(slot);
}

void ClientNetworkModel::subscribeForRotateSignal(sigc::slot<void, int32_t, sf::Vector2f> slot)
{
  handler->subscribeForRotateSignal(slot);
}

void ClientNetworkModel::subscribeForFireSignal(sigc::slot<void, int32_t, sf::Vector2f> slot)
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

ServerNetworkModel::clientPositionUpdated(uint32_t id, sf::Vector2f direction_)
{
  Vector2f direction = convertSFMLtoThrift(v);
  for (auto& service : serverServiceClient)
  {
    service->clientPositionUpdated(id, direction);
  }
}

ServerNetworkModel::clientDirectionUpdated(uint32_t id, sf::Vector2f direction_)
{
  Vector2f direction = convertSFMLtoThrift(v);
  for (auto& service : serverServiceClient)
  {
    service->clientDirectionUpdated(id, direction);
  }
}

ServerNetworkModel::fireUpdated()
{
  /*for (auto& service : serverServiceClient)
  {
    service->clientPositionUpdated(id, direction);
  }*/
}


} // namespace junk

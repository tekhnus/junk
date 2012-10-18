#include "ClientNetworkModel.hpp"

namespace junk
{

ClientNetworkModel::ClientNetworkModel() : logger("client_model.log", "CLIENT_NETWORK_MODEL", true)
{
  handler = boost::shared_ptr<ServerServiceHandler> (new ServerServiceHandler());
  processor = boost::shared_ptr<TProcessor> (new ServerServiceProcessor(handler));
  serverTransport = boost::shared_ptr<TServerTransport> (new TServerSocket(port));
  transportFactory = boost::shared_ptr<TTransportFactory> (new TBufferedTransportFactory());
  protocolFactory = boost::shared_ptr<TProtocolFactory> (new TBinaryProtocolFactory());

  server = boost::shared_ptr<TSimpleServer> 
  	(new TSimpleServer (processor, serverTransport, transportFactory, protocolFactory));
  server->serve();

	logger << "ClientNetworkModel created";
}

void ClientNetworkModel::connectToServer(const std::string& serverIp, int port)
{
  socket = boost::shared_ptr<TTransport> (new TSocket(serverIp, port));
  transport = boost::shared_ptr<TTransport> (new TBufferedTransport(socket));
  protocol = boost::shared_ptr<TProtocol> (new TBinaryProtocol(transport));
  clientServiceClient = boost::shared_ptr<ClientServiceClient> (new ClientServiceClient(protocol));
}

ClientNetworkModel::~ClientNetworkModel()
{
	logger << "ClientNetworkModel destructed";
}

void ClientNetworkModel::subscribeForPositionUpdatedSignal(sigc::slot<void, int32_t, sf::Vector2f> slot)
{
  handler->subscribeForPositionUpdatedSignal(slot);
}

void ClientNetworkModel::subscribeForDirectionUpdatedSignal(sigc::slot<void, int32_t, sf::Vector2f> slot)
{
  handler->subscribeForDirectionUpdatedSignal(slot);
}

ClientNetworkModel::move(sf::Vector2f direction)
{
  ClientServiceClient->move(direction);
}

ClientNetworkModel::rotate(sf::Vector2f direction)
{
  ClientServiceClient->rotate(direction);
}

ClientNetworkModel::fire(sf::Vector2f direction)
{
  ClientServiceClient->fire(direction);
}

} // namespace junk
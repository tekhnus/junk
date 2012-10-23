#include "Client.hpp"

namespace junk
{

Client::Client() : controller(view, model)
{
}

void Client::connectToServer(const std::string& serverIp, int port)
{
	model.connectToServer(serverIp, port);
}

} // namespace junk

int main()
{
	junk::Client client;
	client.connectToServer("192.168.1.1", 8099);
	return 0;
}
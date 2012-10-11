#include "server/Server.hpp"
#include "common/logger/Logger.hpp"

#include <iostream>
#include <string>

#include <SFML/Network.hpp>

void playerConnected (int id)
{
	std::cerr << "Player " << id << " connected!" << std::endl;
}

int main ()
{
	unsigned int port = 7777;
	Server server(port);
	server.subscribeForNewClientSignal( sigc::ptr_fun(&playerConnected) );

	server.start();
}

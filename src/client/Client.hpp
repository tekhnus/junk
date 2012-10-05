#pragma once

#include <SFML/Network.hpp>
#include "logger/Logger.hpp"

class Client
{
public:
	Client();

	~Client();
	
	void connect(sf::IpAddress address, unsigned short port);
	void disconnect();

	void sendDataToServer(sf::Packet packet);
	sf::Packet receiveDataFromServer();

private:
	sf::TcpSocket serverSocket;
	sf::IpAddress serverAddress;
	unsigned short port;

	Logger logger;
};

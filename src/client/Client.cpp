#include "Client.hpp"

Client::Client() : logger("CLIENT")
{
}

Client::~Client()
{
}


void Client::connect(sf::IpAddress address, unsigned short port)
{
	this->port = port;
	this->serverAddress = address;
	serverSocket.setBlocking(true);
	if (serverSocket.connect(address, port) == sf::Socket::Done)
	{
		logger << "Connected to server";
	}
	else
	{
		logger << "Failed to connect to server";
	}
}

void Client::disconnect()
{
	// Send disconnect message to server here
	serverSocket.disconnect();
	port = 0;
	serverAddress = "";
	logger << "Disconnected from server";
}

void Client::sendDataToServer(sf::Packet packet)
{
	try
	{
		serverSocket.send(packet);
		logger << "Packet was sent";
	} catch (...)
	{
		logger << "Failed to send packet";
	}

}

sf::Packet Client::receiveDataFromServer()
{
	sf::Packet packet;
	if (serverSocket.receive(packet) == sf::Socket::Done)
	{
		logger << "Received packet";
	}
	else
	{
		logger << "Failed to receive packet";
	}
	return packet;
}

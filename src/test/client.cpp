#include "client/Client.hpp"
#include "logger/Logger.hpp"

#include <iostream>
#include <string>

#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

int main ()
{
	Client client;

	std::string serverIp;
	std::cout << "Enter server ip:" << std::endl;
	std::cin >> serverIp;
	unsigned int port = 7777;
 
	std::cerr << "Connecting to server..." << std::endl;
	client.connect(serverIp, port);
	std::cerr << "Connected to server" << std::endl;

	std::string message = "connect", answer;
	
	sf::Packet packet;
	packet << message;

	std::cerr << "Sending data to server..." << std::endl;

	client.sendDataToServer(packet);

	std::cerr << "Receiving data from server..." << std::endl;

	packet = client.receiveDataFromServer();

	packet >> answer;

	if (answer == "connection established")
	{
		std::cerr << "connection established" << std::endl;
	}
	else //(answer == "connection refused")
	{
		std::cerr << "connection refused" << std::endl;
	}

	return 0;
}

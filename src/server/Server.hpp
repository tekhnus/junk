#pragma once

#include <SFML/Network.hpp>

#include <sigc++-2.0/sigc++/sigc++.h>

#include <memory>

#include "logger/Logger.hpp"

class Server
{
public:

	struct ClientInfo
	{
		ClientInfo(int id, sf::TcpSocket* socket) : id(id)
		{
			this->socket = std::unique_ptr<sf::TcpSocket> (socket);
		}
		int id;
		std::unique_ptr<sf::TcpSocket> socket;
	};

	enum class ServerSignal
	{
		NEW_CLIENT_SIGNAL,
		PACKET_RECEIVED_SIGNAL
	};

	Server();
	Server(unsigned short port);

	~Server();

	void start();
	void stop();

	void sendDataToClient(int clientId, sf::Packet packet);

	void subscribeForPacketReceivedSignal(sigc::slot<void, int, sf::Packet> packedReceivedSlot);
	void subscribeForNewClientSignal(sigc::slot<void, int> newClientSlot);

private:
	
	void receiveDataFromClient(ClientInfo& client);
	void processRequests();

	void addClient(sf::TcpSocket* newClientSocket);

	sf::TcpListener newClientsListener;
	sf::SocketSelector socketSelector;
	std::unique_ptr<sf::Thread> thread;
	std::vector<ClientInfo> clients;
	unsigned short port;
	size_t clientsNumber;

	sigc::signal<void, int, sf::Packet>	packetReceivedSignal;
	sigc::signal<void, int> newClientSignal;

  	Logger logger;

};

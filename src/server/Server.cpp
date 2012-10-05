#include "Server.hpp"

Server::Server() : logger("SERVER")
{
	clientsNumber = 0;
}

Server::Server(unsigned short port) : logger("SERVER")
{
	clientsNumber = 0;
	this->port = port;
}

Server::~Server()
{
	thread->wait();
}

void Server::start()
{
	newClientsListener.listen(port);
	socketSelector.add(newClientsListener);
	thread = std::unique_ptr<sf::Thread> (new sf::Thread(&Server::processRequests, this));
	thread->launch();
	logger << "Server started";
}

void Server::stop()
{
	thread->terminate();
	logger << "Server terminated";
}

void Server::addClient(sf::TcpSocket* newClient)
{
	clientsNumber++;
	clients.push_back(ClientInfo(clientsNumber, newClient));
	newClientSignal.emit(clientsNumber);
	logger << "Client " + std::to_string(clientsNumber) + " connected";
}

void Server::subscribeForPacketReceivedSignal(sigc::slot<void, int, sf::Packet> packedReceivedSlot)
{
	packetReceivedSignal.connect(packedReceivedSlot);
	logger << "New subscriber for packetReceivedSignal";
}

void Server::subscribeForNewClientSignal(sigc::slot<void, int> newClientSlot)
{
	newClientSignal.connect(newClientSlot);
	logger << "New subscriber for newClientSignal";
}

void Server::receiveDataFromClient(Server::ClientInfo& client)
{
	sf::Packet packet;
	if (client.socket->receive(packet) == sf::Socket::Done)
	{
		packetReceivedSignal.emit(client.id, packet);
		logger << "Received packet from " + std::to_string(client.id);
	}
	else
	{
		logger << "Failed to recieve a packet from " + std::to_string(client.id);
	}
}

void Server::sendDataToClient(int clientId, sf::Packet packet)
{
	for (auto& client : clients)
	{
		if (client.id == clientId)
		{
			client.socket->send(packet);
			logger << "Package to " + std::to_string(clientId) + " was sent";
			return;
		}
	}
	logger << "Client " + std::to_string(clientId) + " not found";
}

void Server::processRequests()
{
	while (true)
	{
		if (socketSelector.wait())
		{
			logger << "New request from some socket";
			if (socketSelector.isReady(newClientsListener))
			{
				sf::TcpSocket* newClientSocket = new sf::TcpSocket;
				if (newClientsListener.accept(*newClientSocket) == sf::Socket::Done)
				{
					addClient(newClientSocket);
					socketSelector.add(*newClientSocket);
				}
			}
			else
			{
				for(auto& client : clients)
				{
					if (socketSelector.isReady(*client.socket))
					{
						receiveDataFromClient(client);
					}
				}
			}
		}
	}
}

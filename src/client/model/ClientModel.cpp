#include "ClientModel.hpp"

namespace junk
{

ClientModel::ClientModel() : logger("CLIENT_MODEL", "client_model.log", true)
{
	logger << "ClientModel created";
}

ClientModel::~ClientModel()
{
	logger << "ClientModel destructed";
}

int32_t ClientModel::connectToServer(const std::string& serverIp, int port)
{
	clientId = networkModel.connectToServer(serverIp, port);
	gotClientIdSignal.emit(clientId);
	return clientId;
}

void ClientModel::update()
{
	logger << "update";
	GameChanges gameChanges = networkModel.getGameChanges();
	for (auto& player : gameChanges.players)
	{
		logger << std::to_string(player.id) + std::string(" ") 
			+ std::to_string(player.position.x) + std::string(" ") + std::to_string(player.position.y);
			
		updatePlayerPosition(player.id, sf::Vector2f(player.position.x, player.position.y));
		updatePlayerDirection(player.id, sf::Vector2f(player.direction.x, player.direction.y));
	}
}

void ClientModel::addPlayer(int32_t id, sf::Vector2f position, sf::Vector2f direction)
{
	logger << "Adding new player";
	players[id] = Player(id, position, direction);
	clientAddedSignal.emit(id, position, direction);
}

void ClientModel::updatePlayerPosition(int32_t id, sf::Vector2f position)
{
	logger << "Updating player position";
	if (players.find(id) == players.end())
	{
		addPlayer(id, position, sf::Vector2f(1.0, 1.0));
	}
	else
	{
		players[id].setPosition(position);
		clientPositionUpdatedSignal.emit(id, position);
		return;
	}
}

void ClientModel::updatePlayerDirection(int32_t id, sf::Vector2f direction)
{
	logger << "Updating player direction";
	if (players.find(id) == players.end())
	{
		addPlayer(id, sf::Vector2f(1.0, 1.0), direction);
	}
	else
	{
		players[id].setDirection(direction);
		clientDirectionUpdatedSignal.emit(id, direction);
		return;
	}
}

void ClientModel::subscribeForGotClientIdSignal(sigc::slot<void, int32_t> slot)
{
	gotClientIdSignal.connect(slot);
}

void ClientModel::subscribeForClientAddedSignal(sigc::slot<void, int32_t, sf::Vector2f, sf::Vector2f> slot)
{
	clientAddedSignal.connect(slot);
}

void ClientModel::subscribeForClientPositionUpdatedSignal(sigc::slot<void, int32_t, sf::Vector2f> slot)
{
	clientPositionUpdatedSignal.connect(slot);
}

void ClientModel::subscribeForClientDirectionUpdatedSignal(sigc::slot<void, int32_t, sf::Vector2f> slot)
{
	clientDirectionUpdatedSignal.connect(slot);
}

void ClientModel::move(sf::Vector2f direction)
{
	networkModel.move(direction);
}

void ClientModel::fire(sf::Vector2f direction)
{
	networkModel.fire(direction);
}

void ClientModel::rotate(sf::Vector2f direction)
{
	networkModel.rotate(direction);
}

} // namespace junk
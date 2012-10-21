#include "ClientModel.hpp"

namespace junk
{

ClientModel::ClientModel() : logger("client_model.log", "CLIENT_MODEL", true)
{
	logger << "ClientModel created";
}

ClientModel::~ClientModel()
{
	logger << "ClientModel destructed";
}

void ClientModel::update()
{
	GameChanges gameChanges = networkModel.getGameChanges();
	for (auto& player : gameChanges.players)
	{
		updatePlayerPosition(player.id, sf::Vector2f(player.position.x, player.position.y));
		updatePlayerDirection(player.id, sf::Vector2f(player.direction.x, player.direction.y));
	}
}

void ClientModel::addPlayer(int32_t id)
{
	logger << "Adding new player";
	players.push_back(Player(id));
	clientAddedSignal.emit(id);
}

void ClientModel::updatePlayerPosition(int32_t id, sf::Vector2f position)
{
	logger << "Updating player position";
	for (Player& player : players)
	{
		if (player.getId() == id)
		{
			player.setPosition(position);
			clientPositionUpdatedSignal.emit(id, position);
			return;
		}
	}
}

void ClientModel::updatePlayerDirection(int32_t id, sf::Vector2f direction)
{
	logger << "Updating player direction";
	for (Player& player : players)
	{
		if (player.getId() == id)
		{
			player.setDirection(direction);
			clientDirectionUpdatedSignal.emit(id, direction);
			return;
		}
	}
}

void ClientModel::subscribeForClientAddedSignal(sigc::slot<void, int32_t> slot)
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
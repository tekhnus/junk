#include "ClientModel.hpp"

namespace junk
{

ClientModel::ClientModel() : logger("client_model.log", "CLIENT_MODEL", true)
{
	networkModel.subscribeForPositionUpdatedSignal(sigc::mem_fun(this, &ClientModel::updatePlayerPosition));
	networkModel.subscribeForDirectionUpdatedSignal(sigc::mem_fun(this, &ClientModel::updatePlayerDirection));
	logger << "ClientModel created";
}

ClientModel::~ClientModel()
{
	logger << "ClientModel destructed";
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
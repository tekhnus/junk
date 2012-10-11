#include "ClientModel.hpp"

namespace junk
{

ClientModel::ClientModel() : logger("client_model.log", "CLIENT_MODEL", true)
{
	serverService.subscribeForPositionUpdatedSignal(sigc::mem_fun(this, &ClientModel::updatePlayerPosition));
	serverService.subscribeForDirectionUpdatedSignal(sigc::mem_fun(this, &ClientModel::updatePlayerDirection));
	logger << "ClientModel created";
}

ClientModel::~ClientModel()
{
	logger << "ClientModel destructed";
}

void ClientModel::updatePlayerPosition(int16_t id, sf::Vector2f position)
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

void ClientModel::updatePlayerDirection(int16_t id, sf::Vector2f direction)
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


void ClientModel::subscribeForClientPositionUpdatedSignal(sigc::slot<void, int16_t, sf::Vector2f> slot)
{
	clientPositionUpdatedSignal.connect(slot);
}

void ClientModel::subscribeForClientDirectionUpdatedSignal(sigc::slot<void, int16_t, sf::Vector2f> slot)
{
	clientDirectionUpdatedSignal.connect(slot);
}

} // namespace junk
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

void ClientModel::updatePlayerPosition(int id, sf::Vector2f position)
{
	logger << "Updating player position";
	for (Player& player : players)
	{
		if (player.getId() == id)
		{
			player.setPosition(position);
			return;
		}
	}
}

void ClientModel::updatePlayerDirection(int id, sf::Vector2f direction)
{
	logger << "Updating player direction";
	for (Player& player : players)
	{
		if (player.getId() == id)
		{
			player.setDirection(direction);
			return;
		}
	}
}

} // namespace junk
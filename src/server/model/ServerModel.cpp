#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include "ServerModel.hpp"

namespace junk
{

ServerModel::ServerModel() : logger("SERVER_MODEL", "server_model.log", true)
{
	gameModel.subscribeForPositionUpdatedSignal(sigc::mem_fun(&networkModel, 
		&ServerNetworkModel::clientPositionUpdated));

	gameModel.subscribeForDirectionUpdatedSignal(sigc::mem_fun(&networkModel, 
		&ServerNetworkModel::clientDirectionUpdated));

	networkModel.subscribeForConnectSignal(sigc::mem_fun(this, &ServerModel::connectHandler));
	networkModel.subscribeForGetChangesSignal(sigc::mem_fun(this, &ServerModel::getChangesHandler));
	networkModel.subscribeForMoveSignal(sigc::mem_fun(this, &ServerModel::moveHandler));
	networkModel.subscribeForRotateSignal(sigc::mem_fun(this, &ServerModel::rotateHandler));
	networkModel.subscribeForFireSignal(sigc::mem_fun(this, &ServerModel::fireHandler));

	logger << "ServerModel created";
}

ServerModel::~ServerModel()
{
	logger << "ServerModel destroyed";
}

void ServerModel::start()
{
	gameModel.start();
}

int32_t ServerModel::connectHandler()
{
	return gameModel.addPlayer();
}

GameChanges ServerModel::getChangesHandler(int32_t id)
{
	GameChanges gameChanges = gameModel.getChanges(id);
	for (auto& player : gameChanges.players)
	{
		logger << std::to_string(player.id) + std::string(" ") 
			+ std::to_string(player.position.x) + std::string(" ") + std::to_string(player.position.y);
	}
	return gameChanges;
}

void ServerModel::moveHandler(int32_t id, sf::Vector2f direction)
{
	gameModel.move(id, direction);
}

void ServerModel::rotateHandler(int32_t id, sf::Vector2f direction)
{
	gameModel.rotate(id, direction);
}

void ServerModel::fireHandler(int32_t id, sf::Vector2f direction)
{
	//gameModel.fire(id, position);
}

} // namespace junk
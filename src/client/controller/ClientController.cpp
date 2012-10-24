#include "ClientController.hpp"

namespace junk
{

ClientController::ClientController(ClientView& view, ClientModel& model) : view(view), model(model), logger("CLIENT_CONTROLLER", "client_controller.log", true)
{
	view.subscribeForFireSignal(sigc::mem_fun(this, &ClientController::fireHandler));
	view.subscribeForMoveSignal(sigc::mem_fun(this, &ClientController::moveHandler));
	view.subscribeForRotateSignal(sigc::mem_fun(this, &ClientController::rotateHandler));

	model.subscribeForClientAddedSignal(sigc::mem_fun(this, &ClientController::clientAddedHandler));
	model.subscribeForClientPositionUpdatedSignal(sigc::mem_fun(this, &ClientController::clientPositionUpdatedHandler));
	model.subscribeForClientDirectionUpdatedSignal(sigc::mem_fun(this, &ClientController::clientDirectionUpdatedHandler));

	logger << "ClientController created";
}

ClientController::~ClientController()
{
	logger << "ClientController destructed";
}

void ClientController::clientAddedHandler(int32_t id)
{
	logger << "clientAddedHandler invoked";
	//view.addPlayer(id);
}

void ClientController::moveHandler(sf::Vector2f direction)
{
	logger << "moveHandler invoked";
	model.move(direction);
}

void ClientController::fireHandler(sf::Vector2f direction)
{
	logger << "fireHandler invoked";
	model.fire(direction);
}

void ClientController::rotateHandler(sf::Vector2f direction)
{
	logger << "rotateHandler invoked";
	model.rotate(direction);
}

void ClientController::clientPositionUpdatedHandler(int32_t id, sf::Vector2f position)
{
	logger << "clientPositionUpdatedHandler invoked";
	view.setPlayerPosition(id, position);
}

void ClientController::clientDirectionUpdatedHandler(int32_t id, sf::Vector2f direction)
{
	logger << "clientDirectionUpdatedHandler invoked";
	view.setPlayerRotation(id, direction);
}

} // namespace junk
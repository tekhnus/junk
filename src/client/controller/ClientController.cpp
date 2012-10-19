#include "ClientController.hpp"

namespace junk
{

ClientController::ClientController(ClientView& view, ClientModel& model) : view(view), model(model), logger("client_controller.log", "CLIENT_CONTROLLER", true)
{
	view.subscribeForFireSignal(sigc::mem_fun(this, &ClientController::fireHandler));
	view.subscribeForMoveSignal(sigc::mem_fun(this, &ClientController::moveHandler));
	view.subscribeForRotateSignal(sigc::mem_fun(this, &ClientController::rotateHandler));

	model.subscribeForClientPositionUpdatedSignal(sigc::mem_fun(this, &ClientController::clientPositionUpdatedHandler));
	model.subscribeForClientDirectionUpdatedSignal(sigc::mem_fun(this, &ClientController::clientDirectionUpdatedHandler));

	logger << "ClientController created";
}

ClientController::~ClientController()
{
	logger << "ClientController destructed";
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

void ClientController::clientPositionUpdatedHandler(int16_t id, sf::Vector2f direction)
{
		logger << "clientPositionUpdatedHandler invoked";
}

void ClientController::clientDirectionUpdatedHandler(int16_t id, sf::Vector2f direction)
{
		logger << "clientDirectionUpdatedHandler invoked";
}

} // namespace junk
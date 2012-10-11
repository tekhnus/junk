#include "ClientController.hpp"

namespace junk
{

ClientController::ClientController(ClientView& view, ClientModel& model) : view(view), model(model), logger("client_controller.log", "CLIENT_CONTROLLER", true)
{
	view.subscribeForFireSignal(sigc::mem_fun(this, &fireHandler));
	view.subscribeForMoveSignal(sigc::mem_fun(this, &moveHandler));
	view.subscribeForRotateSignal(sigc::mem_fun(this, &rotateHandler));

	model.subscribeForClientPositionUpdatedSignal(sigc::mem_fun(this, &clientPositionUpdatedHandler));
	model.subscribeForClientDirectionUpdatedSignal(sigc::mem_fun(this, &clientDirectionUpdatedHandler)));

	logger << "ClientController created";
}

ClientController::~ClientController()
{
	logger << "ClientController destructed";
}

void ClientController::moveHandler(sf::Vector2f direction)
{
	logger << "moveHandler invoked";
}

void ClientController::fireHandler(sf::Vector2f direction)
{
	logger << "fireHandler invoked";
}

void ClientController::rotateHandler(sf::Vector2f direction)
{
	logger << "rotateHandler invoked";
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
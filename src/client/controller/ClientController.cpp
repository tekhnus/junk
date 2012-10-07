#include "ClientController.hpp"

namespace junk
{

ClientController::ClientController(ClientView& view, ClientModel& model) : view(view), model(model), logger("client_controller.log", "CLIENT_CONTROLLER", true)
{
	view.subscribeForFireSignal(sigc::mem_fun(this, &fireHandler));
	view.subscribeForMoveSignal(sigc::mem_fun(this, &moveHandler));
	view.subscribeForRotateSignal(sigc::mem_fun(this, &rotateHandler));

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

} // namespace junk
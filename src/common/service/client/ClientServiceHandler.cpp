#include "ClientServiceHandler.hpp"

namespace junk
{
	ClientServiceHandler::ClientServiceHandler()
	{
	}

	int32_t ClientServiceHandler::connect()
	{
		connectSignal.emit(0);
	}

	void ClientServiceHandler::move(int32_t id, const Vector2f& direction)
	{
		moveSignal.emit(id, sf::Vector2f(direction.x, direction.y));
	}

	void ClientServiceHandler::rotate(int32_t id, const Vector2f& direction)
	{
		rotateSignal.emit(id, sf::Vector2f(direction.x, direction.y));
	}

	void ClientServiceHandler::fire(int32_t id, const Vector2f& direction)
	{
		fireSignal.emit(id, sf::Vector2f(direction.x, direction.y));
	}

	void ClientServiceHandler::getChanges(GameChanges& gameChanges, int32_t id)
	{
	}

	void ClientServiceHandler::subscribeForConnectSignal(sigc::slot<void, int32_t> slot)
	{
		connectSignal.connect(slot);
	}

	void ClientServiceHandler::subscribeForMoveSignal(sigc::slot<void, int32_t, sf::Vector2f> slot)
	{
		moveSignal.connect(slot);
	}

	void ClientServiceHandler::subscribeForRotateSignal(sigc::slot<void, int32_t, sf::Vector2f> slot)
	{
		rotateSignal.connect(slot);
	}

	void ClientServiceHandler::subscribeForFireSignal(sigc::slot<void, int32_t, sf::Vector2f> slot)
	{
		fireSignal.connect(slot);
	}
	
} // namespace junk
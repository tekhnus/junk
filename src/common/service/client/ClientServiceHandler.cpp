#include "ClientServiceHandler.hpp"

namespace junk
{
	ClientServiceHandler::ClientServiceHandler()
	{
	}

	void ClientServiceHandler::move(uint32_t id, const Vector2f& direction)
	{
		moveSignal.emit(id, sf::Vector2f(direction.x, direction.y));
	}

	void ClientServiceHandler::rotate(uint32_t id, const Vector2f& direction)
	{
		rotateSignal.emit(id, sf::Vector2f(direction.x, direction.y));
	}

	void ClientServiceHandler::fire(uint32_t id, const Vector2f& direction)
	{
		fireSignal.emit(id, sf::Vector2f(direction.x, direction.y));
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
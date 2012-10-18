#include "ServerServiceHandler.hpp"

namespace junk
{
	ServerServiceHandler::ServerServiceHandler()
	{
	}

	void ServerServiceHandler::subscribeForPositionUpdatedSignal(sigc::slot<void, int32_t, sf::Vector2f> slot)
	{
		clientPositionUpdatedSignal.connect(slot);
	}

	void ServerServiceHandler::subscribeForDirectionUpdatedSignal(sigc::slot<void, int32_t, sf::Vector2f> slot)
	{
		clientDirectionUpdatedSignal.connect(slot);
	}

	void ServerServiceHandler::clientPositionUpdated(const int32_t id, const Vector2f& position)
	{
		clientPositionUpdatedSignal.emit(id, sf::Vector2f(position.x, position.y));
	}

	void ServerServiceHandler::clientDirectionUpdated(const int32_t id, const Vector2f& direction)
	{
		clientDirectionUpdatedSignal.emit(id, sf::Vector2f(direction.x, direction.y));
	}

	void ServerServiceHandler::fireUpdated()
	{
	}

} // namespace junk
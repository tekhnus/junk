#pragma once

#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include <common/logger/Logger.hpp>

#include <gen-cpp/ServerService.h>

namespace junk
{
	class ServerServiceHandler : virtual public ServerServiceIf
	{
	public:
		ServerServiceHandler();
		~ServerServiceHandler();

		void clientPositionUpdated(const int32_t id, const Vector2f& position);
		void clientDirectionUpdated(const int32_t id, const Vector2f& direction);
		void fireUpdated();

		void subscribeForPositionUpdatedSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);
		void subscribeForDirectionUpdatedSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);

	private:
		sigc::signal<void, int32_t, sf::Vector2f> clientPositionUpdatedSignal;
		sigc::signal<void, int32_t, sf::Vector2f> clientDirectionUpdatedSignal;

	}; // ServerServiceHandle

} // namespace junk

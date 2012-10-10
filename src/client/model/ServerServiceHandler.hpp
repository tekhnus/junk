#pragma once

#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include <logger/Logger.hpp>
#include <client/model/gen-cpp/ServerService.h>

namespace junk
{
	class ServerServiceHandler : virtual public ServerServiceIf
	{
	public:
		ServerServiceHandler();
		~ServerServiceHandler();

		void clientPositionUpdated(const int16_t id, const Vector2f& position);
		void clientDirectionUpdated(const int16_t id, const Vector2f& direction);
		void fireUpdated();

	private:
	}; // ServerServiceHandle

} // namespace junk
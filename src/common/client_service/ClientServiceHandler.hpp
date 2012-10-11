#pragma once

#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include <common/logger/Logger.hpp>

#include "gen-cpp/ClientService.h"

namespace junk
{
	class ClientServiceHandler : virtual public ClientServiceIf
	{
	public:
		ClientServiceHandler();
		~ClientServiceHandler();

		void move(const Vector2f& direction);
		void changeDirection(const Vector2f& direction);
		void fire(const Vector2f& direction);

	private:
	}; // ClientServiceHandle

} // namespace junk

#pragma once

#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include <common/logger/Logger.hpp>

#include <common/service/gen-cpp/ClientService.h>

namespace junk
{
	class ClientServiceHandler : virtual public ClientServiceIf
	{
	public:
		ClientServiceHandler();
		~ClientServiceHandler();

		void connect();
		void move(uint32_t id, const Vector2f& direction);
		void rotate(uint32_t id, const Vector2f& direction);
		void fire(uint32_t id, const Vector2f& direction);

		void subscribeForConnectSignal();
		void subscribeForMoveSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);
		void subscribeForRotateSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);
		void subscribeForFireSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);

	private:
		sigc::signal<void, uint32_t, sf::Vector2f> connectSignal;
		sigc::signal<void, uint32_t, sf::Vector2f> moveSignal;
		sigc::signal<void, uint32_t, sf::Vector2f> rotateSignal;
		sigc::signal<void, uint32_t, sf::Vector2f> fireSignal;

	}; // ClientServiceHandle

} // namespace junk

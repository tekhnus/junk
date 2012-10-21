#pragma once

#include <SFML/System.hpp>
#include <sigc++/sigc++.h>
#include <common/logger/Logger.hpp>

#include <gen-cpp/ClientService.h>

namespace junk
{
	class ClientServiceHandler : virtual public ClientServiceIf
	{
	public:
		ClientServiceHandler();
		~ClientServiceHandler();

		int32_t connect();
		void getChanges(GameChanges& gameChanges, int32_t id);
		void move(int32_t id, const Vector2f& direction);
		void rotate(int32_t id, const Vector2f& direction);
		void fire(int32_t id, const Vector2f& direction);

		void subscribeForConnectSignal(sigc::slot<int32_t> slot);
		void subscribeForGetChangesSignal(sigc::slot<GameChanges, int32_t> slot);
		void subscribeForMoveSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);
		void subscribeForRotateSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);
		void subscribeForFireSignal(sigc::slot<void, int32_t, sf::Vector2f> slot);

	private:
		sigc::signal<int32_t> connectSignal;
		sigc::signal<GameChanges, int32_t> getChangesSignal;
		sigc::signal<void, int32_t, sf::Vector2f> moveSignal;
		sigc::signal<void, int32_t, sf::Vector2f> rotateSignal;
		sigc::signal<void, int32_t, sf::Vector2f> fireSignal;

	}; // ClientServiceHandle

} // namespace junk

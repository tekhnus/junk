#pragma once

#include "Unit.hpp"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <sigc++/sigc++.h>

#include <common/logger/Logger.hpp>

#include <map>
#include <cassert>
#define _GLIBCXX_USE_NANOSLEEP
#include <thread>

namespace junk
{

typedef unsigned int IDType;

class ClientView : public sf::Drawable
{
public:
	ClientView();
	virtual ~ClientView();

	void addPlayer(IDType playerID, sf::Vector2f position, sf::Vector2f rotation);
	void removePlayer(IDType playerID);

	void setPlayerPosition(IDType playerID, sf::Vector2f position);
	void setPlayerRotation(IDType playerID, sf::Vector2f rotation);

	void move(sf::Vector2f direction);
	void rotate(sf::Vector2f rotation);

	bool subscribeForFireSignal(sigc::slot<void, sf::Vector2f> slot);
	bool subscribeForMoveSignal(sigc::slot<void, sf::Vector2f> slot);
	bool subscribeForRotateSignal(sigc::slot<void, sf::Vector2f> slot);

	void setClientID (IDType clientID);
	void update();

private:
	std::map<IDType, PlayerUnit> players;
	sigc::signal<void, sf::Vector2f> fireSignal;
	sigc::signal<void, sf::Vector2f> moveSignal;
	sigc::signal<void, sf::Vector2f> rotateSignal;

	IDType clientID;
	void processInput();
	Logger logger;
	std::thread inputThread;
	bool prevUp, prevDown, prevLeft, prevRight;


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}

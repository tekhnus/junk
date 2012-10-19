#pragma once

#include "SFML/System.hpp"
#include "Unit.hpp"
#include "sigc++/sigc++.h"
#include <map>
#include <thread>
#include <mutex>

namespace junk
{

typedef int32_t PlayerIDType;

class ServerGameModel
{
public:
	ServerGameModel();
	~ServerGameModel();

	void start();
	void stop();

	void addPlayer(sf::Vector2f position, sf::Vector2f rotation);
	void removePlayer(PlayerIDType playerID);
	void move(PlayerIDType playerID, sf::Vector2f position);
	void rotate(PlayerIDType playerID, sf::Vector2f rotation);
	//void fire(PlayerIDType playerID);

	//bool subscribeForFireSignal(sigc::slot<void, PlayerIDType, sf::Vector2f> slot);
	bool subscribeForPositionUpdatedSignal(sigc::slot<void, PlayerIDType, sf::Vector2f> slot);
	bool subscribeForDirectionUpdatedSignal(sigc::slot<void, PlayerIDType, sf::Vector2f> slot);
	void operator()();
private:
	

	std::map<PlayerIDType, unit::Player> players;

	bool isRunning;
	sf::Clock gameLoopTimer;

	std::thread gameLoopThread;
	std::mutex gameChangesMutex;

	//sigc::signal<void, PlayerIDType, sf::Vector2f> fireSignal;
	sigc::signal<void, PlayerIDType, sf::Vector2f> positionUpdatedSignal;
	sigc::signal<void, PlayerIDType, sf::Vector2f> directionUpdatedSignal;

};

}

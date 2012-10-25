#pragma once

#include "SFML/System.hpp"
#include "Unit.hpp"
#include <common/logger/Logger.hpp>
#include "sigc++/sigc++.h"
#include <map>
#include <thread>
#include <mutex>

#include <gen-cpp/ClientService.h>

namespace junk
{

typedef int32_t IDType;

class ServerGameModel
{
public:
	ServerGameModel();
	~ServerGameModel();

	void start();
	void stop();

	IDType addPlayer(sf::Vector2f position = sf::Vector2f(0.0, 0.0), 
		sf::Vector2f rotation = sf::Vector2f(1.0, 1.0));
	void removePlayer(IDType playerID);
	void move(IDType playerID, sf::Vector2f position);
	void rotate(IDType playerID, sf::Vector2f rotation);
	//void fire(IDType playerID);

	GameChanges getChanges(IDType id);


	//bool subscribeForFireSignal(sigc::slot<void, IDType, sf::Vector2f> slot);
	void subscribeForPositionUpdatedSignal(sigc::slot<void, IDType, sf::Vector2f> slot);
	void subscribeForDirectionUpdatedSignal(sigc::slot<void, IDType, sf::Vector2f> slot);
	void operator()();

private:
	std::map<IDType, std::shared_ptr<unit::Unit>> units;
	//std::map<IDType, unit::Player> players;
	//std::map<IDType, unit::Bullet> bullets;

	bool isRunning;
	sf::Clock gameLoopTimer;

	std::thread gameLoopThread;
	std::mutex gameChangesMutex;

	//sigc::signal<void, IDType, sf::Vector2f> fireSignal;
	sigc::signal<void, IDType, sf::Vector2f> positionUpdatedSignal;
	sigc::signal<void, IDType, sf::Vector2f> directionUpdatedSignal;

	Logger logger;

};

} // namespace junk

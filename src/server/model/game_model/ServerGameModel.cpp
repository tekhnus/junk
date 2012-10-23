#include "ServerGameModel.hpp"
#include "sigc++/sigc++.h"
#include <functional>

namespace junk
{

ServerGameModel::ServerGameModel()
 : isRunning(false)
{
}

void ServerGameModel::start()
{
	isRunning = true;
	gameLoopTimer.restart();
	gameLoopThread = std::thread(std::ref(*this));
}

void ServerGameModel::stop()
{
	gameChangesMutex.lock();
	isRunning = false;
	gameChangesMutex.unlock();

	gameLoopThread.join();
}

void ServerGameModel::addPlayer(sf::Vector2f position, sf::Vector2f rotation)
{
	gameChangesMutex.lock();

	IDType newPlayerID = 0;
	for (auto &unit : units)
	{
		if (newPlayerID == unit.first)
		{
			newPlayerID++;
		}
	}

	std::shared_ptr<unit::Unit> newPlayerPtr;
	newPlayerPtr = std::move(std::shared_ptr<unit::Unit>(new unit::Player(position, rotation)));

	units.insert(std::make_pair(newPlayerID, std::move(newPlayerPtr)));

	gameChangesMutex.unlock();
}

void ServerGameModel::removePlayer(IDType playerID)
{
	gameChangesMutex.lock();

	units.erase(playerID);

	gameChangesMutex.unlock();
}

void ServerGameModel::move(IDType playerID, sf::Vector2f vector)
{
	static const float speed = 25.0; // will be deleted

	gameChangesMutex.lock();

	if (units.find(playerID) != units.end())
	{	
		units.at(playerID)->setMoveVector(vector);
		units.at(playerID)->setMoveSpeed(speed);
	}

	gameChangesMutex.unlock();
}

void ServerGameModel::rotate(IDType playerID, sf::Vector2f rotation)
{
	gameChangesMutex.lock();

	if (units.find(playerID) != units.end())
	{
		dynamic_cast<unit::RotatableUnit*>(units.at(playerID).get())->setPosition(rotation);

	}
	directionUpdatedSignal(playerID, rotation);

	gameChangesMutex.unlock();
}

/*void ServerGameModel::fire(IDType playerID)
{
	gameChangesMutex.lock();

	gameChangesMutex.unlock();
}*/

/*bool ServerGameModel::subscribeForFireSignal(sigc::slot<void, IDType, sf::Vector2f> slot)
{
	fireSignal.connect(slot);
}*/

void ServerGameModel::subscribeForPositionUpdatedSignal(sigc::slot<void, IDType, sf::Vector2f> slot)
{
	positionUpdatedSignal.connect(slot);
}

void ServerGameModel::subscribeForDirectionUpdatedSignal(sigc::slot<void, IDType, sf::Vector2f> slot)
{
	directionUpdatedSignal.connect(slot);
}

void ServerGameModel::operator()()
{
	while (true)
	{	
		gameChangesMutex.lock();

		if (!isRunning)
		{
			gameChangesMutex.unlock();
			break;
		}

		for (auto &unit : units)
		{
			unit.second->synchronize(gameLoopTimer);
		}

		/*for (auto player : players)
		{
			for (auto bullet : bullets)
			{
				if (player.second.interactsWith(bullet.second))
				{
				}
			}
		}*/

		gameChangesMutex.unlock();
	}

	return;
} // namespace unit

} // namespace junk

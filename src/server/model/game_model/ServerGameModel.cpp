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
	gameLoopThread=std::thread(std::ref(*this));
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

	PlayerIDType newPlayerID = 0;
	for (auto player : players)
	{
		if (newPlayerID == player.first)
		{
			newPlayerID++;
		}
	}
	players.insert(std::make_pair(newPlayerID,unit::Player(position, rotation)));
	gameLoopTimer.restart();

	gameChangesMutex.unlock();
}

void ServerGameModel::removePlayer(PlayerIDType playerID)
{
	gameChangesMutex.lock();

	players.erase(playerID);
	gameLoopTimer.restart();

	gameChangesMutex.unlock();
}

void ServerGameModel::move(PlayerIDType playerID, sf::Vector2f vector)
{
	static const float moveSpeed = 25.0; // wiil be removed

	gameChangesMutex.lock();

	if (players.find(playerID) != players.end())
	{
		float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
		vector /= length;
		vector *= moveSpeed;
		vector *= gameLoopTimer.getElapsedTime().asSeconds();

		players.at(playerID).movePosition(vector);
		positionUpdatedSignal(playerID, players.at(playerID).getPosition() + vector);
	}
	gameLoopTimer.restart();

	gameChangesMutex.unlock();
}

void ServerGameModel::rotate(PlayerIDType playerID, sf::Vector2f rotation)
{
	gameChangesMutex.lock();

	if (players.find(playerID) != players.end())
	{
		players.at(playerID).setRotation(rotation);
	}
	directionUpdatedSignal(playerID, rotation);
	gameLoopTimer.restart();

	gameChangesMutex.unlock();
}

/*void ServerGameModel::fire(PlayerIDType playerID)
{
	gameChangesMutex.lock();

	gameLoopTimer.restart();

	gameChangesMutex.unlock();
}*/

/*bool ServerGameModel::subscribeForFireSignal(sigc::slot<void, PlayerIDType, sf::Vector2f> slot)
{
	fireSignal.connect(slot);
}*/

void ServerGameModel::subscribeForPositionUpdatedSignal(sigc::slot<void, PlayerIDType, sf::Vector2f> slot)
{
	positionUpdatedSignal.connect(slot);
}

void ServerGameModel::subscribeForDirectionUpdatedSignal(sigc::slot<void, PlayerIDType, sf::Vector2f> slot)
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
		gameLoopTimer.restart();

		gameChangesMutex.unlock();
	}

	return;
}

}

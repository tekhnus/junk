#include "view/View.hpp"

namespace junk
{

View::View()
{
}

View::~View()
{
}

PlayerIDType View::addPlayer(sf::Vector2f position, sf::Vector2f rotation)
{
	PlayerIDType newPlayerID = 0;
	for (auto player : players)
	{
		if (player.first == newPlayerID)
		{
			newPlayerID++;
		}
	}

	players[newPlayerID] = PlayerUnit(std::to_string(newPlayerID), position, rotation);
	return newPlayerID;
}

void View::removePlayer(PlayerIDType playerID)
{
	players.erase(playerID);
}

void View::setPlayerPosition(PlayerIDType playerID, sf::Vector2f position)
{
	if (players.find(playerID) != players.end())
	{
		players[playerID].setPosition(position);
	}
}

void View::setPlayerRotation(PlayerIDType playerID, sf::Vector2f rotation)
{
	if (players.find(playerID) != players.end())
	{
		players[playerID].setRotation(rotation);
	}
}

bool View::subscribeForFireSignal(sigc::slot<void, sf::Vector2f> slot)
{
	fireSignal.connect(slot);
	return true;
}

bool View::subscribeForMoveSignal(sigc::slot<void, sf::Vector2f> slot)
{
	moveSignal.connect(slot);
	return true;
}

bool View::subscribeForRotateSignal(sigc::slot<void, sf::Vector2f> slot)
{
	rotateSignal.connect(slot);
	return true;
}

void View::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto player : players)
	{
		target.draw(player.second, states);
	}
}

}
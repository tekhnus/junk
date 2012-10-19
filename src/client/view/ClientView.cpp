#include "ClientView.hpp"

namespace junk
{

ClientView::ClientView()
{
}

ClientView::~ClientView()
{
}

PlayerIDType ClientView::addPlayer(sf::Vector2f position, sf::Vector2f rotation)
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

void ClientView::removePlayer(PlayerIDType playerID)
{
	players.erase(playerID);
}

void ClientView::setPlayerPosition(PlayerIDType playerID, sf::Vector2f position)
{
	if (players.find(playerID) != players.end())
	{
		players[playerID].setPosition(position);
	}
}

void ClientView::setPlayerRotation(PlayerIDType playerID, sf::Vector2f rotation)
{
	if (players.find(playerID) != players.end())
	{
		players[playerID].setRotation(rotation);
	}
}

bool ClientView::subscribeForFireSignal(sigc::slot<void, sf::Vector2f> slot)
{
	fireSignal.connect(slot);
	return true;
}

bool ClientView::subscribeForMoveSignal(sigc::slot<void, sf::Vector2f> slot)
{
	moveSignal.connect(slot);
	return true;
}

bool ClientView::subscribeForRotateSignal(sigc::slot<void, sf::Vector2f> slot)
{
	rotateSignal.connect(slot);
	return true;
}

void ClientView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto player : players)
	{
		target.draw(player.second, states);
	}
}

}

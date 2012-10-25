	#include "ClientView.hpp"

namespace junk
{

ClientView::ClientView() : logger("CLIENT_VIEW", "client_view.log", true)
{
}

ClientView::~ClientView()
{
}

void ClientView::addPlayer(IDType playerID, sf::Vector2f position, sf::Vector2f rotation)
{
	assert(players.find(playerID) == players.end());
	players[playerID] = PlayerUnit(std::to_string(playerID), position, rotation);
}

void ClientView::removePlayer(IDType playerID)
{
	players.erase(playerID);
}

void ClientView::setPlayerPosition(IDType playerID, sf::Vector2f position)
{
	logger << std::string("setPlayerPosition invoked, id = ") + std::to_string(playerID);
	logger << std::string("position ") + std::to_string(position.x) + std::string(" ") + std::to_string(position.y);
	if (players.find(playerID) != players.end())
	{
		players[playerID].setPosition(position);
	}
}

void ClientView::setPlayerRotation(IDType playerID, sf::Vector2f rotation)
{
	logger << std::string("setPlayerRotation invoked, id = ") + std::to_string(playerID);
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

void ClientView::move(sf::Vector2f direction)
{
	logger << "move invoked";
	moveSignal.emit(direction);
}

void ClientView::update()
{
	for (auto& player : players)
	{
		logger << std::string("Position.x ") + std::to_string(player.second.getRotation().x);
		logger << std::string("Position.y ") + std::to_string(player.second.getRotation().y);
		logger << std::string("Rotation.x ") + std::to_string(player.second.getRotation().x);
		logger << std::string("Rotation.y ") + std::to_string(player.second.getRotation().y);
		player.second.update();
	}
}

void ClientView::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& player : players)
	{
		target.draw(player.second, states);
	}
}

}

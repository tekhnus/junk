#include "Unit.hpp"

namespace junk
{

namespace unit
{

void Synchronized::synchronize(const sf::Clock &timer)
{
	sf::Time dTime = updateTime(timer);
	sync(dTime);
}

sf::Time Synchronized::updateTime(const sf::Clock &timer)
{
	sf::Time dTime = timer.getElapsedTime() - lastUpdate;
	lastUpdate += dTime;
	return dTime;
}

Unit::Unit(sf::Vector2f position) : position(position)
{
}

void Unit::setPosition(sf::Vector2f position)
{
	this->position = position;
}

sf::Vector2f Unit::getPosition()const
{
	return position;
}

RotatableUnit::RotatableUnit(sf::Vector2f position, sf::Vector2f rotation)
 : Unit(position), rotation(rotation)
{
	if (std::fabs(rotation.x) < eps && std::fabs(rotation.y) < eps)
	{
		this->rotation = sf::Vector2f(1.0, 1.0);
	}
}

void RotatableUnit::setRotation(sf::Vector2f rotation)
{
	if (std::fabs(rotation.x) > eps || std::fabs(rotation.y) > eps)
	{
		this->rotation = rotation;
	}
	else
	{
		this->rotation = sf::Vector2f(1,1);
	}
}

sf::Vector2f RotatableUnit::getRotation()const
{
	return rotation;
}

void RotatableUnit::sync(sf::Time dTime)
{
	static const float moveSpeed = 25.0; // wiil be removed

	sf::Vector2f rotation = getRotation();

	float length = std::sqrt(rotation.x * rotation.x + rotation.y * rotation.y);
	rotation /= length;
	rotation *= moveSpeed;
	rotation *= dTime.asSeconds();

	setPosition(getPosition() + rotation);
}

Player::Player(sf::Vector2f position, sf::Vector2f rotation)
 : RotatableUnit(position, rotation)
{
}

Bullet::Bullet(sf::Vector2f position, sf::Vector2f rotation)
 : RotatableUnit(position, rotation)
{
}

}

}

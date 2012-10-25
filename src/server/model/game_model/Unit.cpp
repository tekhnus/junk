#include "Unit.hpp"

#include <iostream>

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

Unit::Unit(sf::Vector2f position)
 : position(position), moveVector(sf::Vector2f(0.0, 0.0)), moveSpeed(0.0)
{
}

void Unit::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void Unit::setMoveVector(sf::Vector2f moveVector)
{
	this->moveVector = moveVector;
}

void Unit::setMoveSpeed(float moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

sf::Vector2f Unit::getPosition()const
{
	return position;
}

sf::Vector2f Unit::getMoveVector()const
{
	return moveVector;
}

float Unit::getMoveSpeed()const
{
	return moveSpeed;
}

bool Unit::interactsWith(const Unit &unit)const
{
	float dx = fabs(position.x - unit.position.x);
	float dy = fabs(position.y - unit.position.y);
	float dist = sqrt(dx * dx + dy * dy);

	return dist < actionRadius + unit.actionRadius + eps;
}

void Unit::sync(sf::Time dTime)
{
	float length = std::sqrt(moveVector.x * moveVector.x + moveVector.y * moveVector.y);
	if (length < 1e-3)
		return;
	moveVector /= length;
	moveVector *= moveSpeed;
	moveVector *= dTime.asSeconds();

	std::cerr << length << std::endl;
	std::cerr << dTime.asSeconds() << std::endl;
	std::cerr << moveVector.x << " " << moveVector.y << std::endl;

	setPosition(getPosition() + moveVector);
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
		this->rotation = sf::Vector2f(1.0, 1.0);
	}
}

sf::Vector2f RotatableUnit::getRotation()const
{
	return rotation;
}

Player::Player(sf::Vector2f position, sf::Vector2f rotation)
 : RotatableUnit(position, rotation), hp(5)
{
}

Bullet::Bullet(sf::Vector2f position, sf::Vector2f rotation)
 : RotatableUnit(position, rotation)
{
}

} // namespace unit

} // namespace junk

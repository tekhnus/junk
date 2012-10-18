#include <cmath>
#include "Unit.hpp"

namespace junk
{

namespace unit
{

const float unitEps = 1e-5;

Unit::Unit(sf::Vector2f position) : position(position)
{
	if (std::fabs(rotation.x) < eps && std::fabs(rotation.y) < eps)
	{
		this->rotation = sf::Vector2f(1.0, 1.0);
	}
}

void Unit::movePosition(sf::Vector2f vector)
{
	this->position += vector;
}

RotatableUnit::RotatableUnit(sf::Vector2f position, sf::Vector2f rotation)
 : Unit(position), rotation(rotation)
{

}

RotatableUnit::setRotation(sf::Vector2f rotation)
{
	if (std::fabs(rotation.x) > eps || std::fabs(rotation.y) > eps)
	{
		this->rotation = rotation;
	}
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
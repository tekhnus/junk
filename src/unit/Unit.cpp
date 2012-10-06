#include "Unit.hpp"

Unit::Unit (const std::string& name, sf::Vector2i position)
	: name(name), position(position)
{

}

void Unit::moveTo (sf::Vector2i target)
{
	position = target;
}

void Unit::moveAlong (sf::Vector2i vector)
{
	position += vector;
}

void Unit::rename (const std::string &newName)
{
	name = newName;
}

sf::Vector2i Unit::getPosition () const
{
	return position;
}

std::string Unit::getName () const
{
	return name;
}

PlayerUnit::PlayerUnit (const std::string& name, sf::Vector2i position)
		: Unit(name, position), Drawable()
{
	circle.setRadius(10.0);
}

PlayerUnit::~PlayerUnit ()
{
}

void PlayerUnit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(circle, states);
}

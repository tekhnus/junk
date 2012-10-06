#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <cstdlib>

class Unit
{
public:
	explicit Unit (const std::string& name = "", sf::Vector2i position = sf::Vector2i(0, 0));
	virtual ~Unit (){}

	void moveTo (sf::Vector2i target);
	void moveAlong (sf::Vector2i vector);
	void rename (const std::string &newName);

	sf::Vector2i getPosition () const;
	std::string getName () const;
	
private:
	std::string name;
	sf::Vector2i position;

};


class PlayerUnit : public Unit, public sf::Drawable
{
public:
	explicit PlayerUnit (const std::string& name = "", sf::Vector2i position = sf::Vector2i(0, 0));
	virtual ~PlayerUnit ();

private:
	sf::CircleShape circle;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
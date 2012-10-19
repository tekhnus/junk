#pragma once 

#include <cmath>
#include <SFML/System.hpp>

namespace junk
{

namespace unit
{

class Unit
{
public:
//	explicit Unit();
	explicit Unit(sf::Vector2f position);
	virtual ~Unit(){}

	sf::Vector2f getPosition()const;
	void movePosition(sf::Vector2f vector);

private:	
	sf::Vector2f position;

};

class RotatableUnit : public Unit
{
public:
	RotatableUnit(sf::Vector2f position, sf::Vector2f rotation);
	~RotatableUnit(){}

	void setRotation(sf::Vector2f rotation);

private:
	sf::Vector2f rotation;

};

class Player : public RotatableUnit
{
public:
//	Player();
	Player(sf::Vector2f position, sf::Vector2f rotation);
	~Player(){}

private:

};

class Bullet : public RotatableUnit
{
public:
	Bullet(sf::Vector2f position, sf::Vector2f rotation);
	~Bullet(){};

private:

};

} // namespace unit

} // namespace junk

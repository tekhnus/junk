#pragma once 

#include <cmath>
#include <SFML/System.hpp>

namespace junk
{

namespace unit
{

const float eps = 1e-5;

class Synchronized
{
public:
	void synchronize(const sf::Clock &timer);

protected:
	virtual void sync(sf::Time dTime){};
	sf::Time updateTime(const sf::Clock &timer);

	sf::Time lastUpdate;
};

class Unit : public Synchronized
{
public:
//	explicit Unit();
	explicit Unit(sf::Vector2f position);
	virtual ~Unit(){}

	void setPosition(sf::Vector2f position);
	sf::Vector2f getPosition()const;
//	void movePosition(sf::Vector2f vector);

private:	
	sf::Vector2f position;

};

class RotatableUnit : public Unit
{
public:
	RotatableUnit(sf::Vector2f position, sf::Vector2f rotation);
	~RotatableUnit(){}

	void setRotation(sf::Vector2f rotation);
	sf::Vector2f getRotation()const;

private:
	sf::Vector2f rotation;

protected:
	void sync(sf::Time dTime);

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

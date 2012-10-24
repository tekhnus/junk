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
	explicit Unit(sf::Vector2f position);
	virtual ~Unit(){}

	void setPosition(sf::Vector2f position);
	void setMoveVector(sf::Vector2f moveVector);
	void setMoveSpeed(float);

	sf::Vector2f getPosition()const;
	sf::Vector2f getMoveVector()const;
	float getMoveSpeed()const;

	bool interactsWith(const Unit &unit)const;

private:	
	sf::Vector2f position;
	sf::Vector2f moveVector;
	float actionRadius;
	float moveSpeed;

protected:
	void sync(sf::Time dTime);

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

};

class Player : public RotatableUnit
{
public:
	Player(sf::Vector2f position, sf::Vector2f rotation);
	~Player(){}

private:
	int hp;

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

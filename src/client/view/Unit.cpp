#include "Unit.hpp"

namespace junk
{

Unit::Unit(const std::string& name, sf::Vector2f position, sf::Vector2f rotation)
: name(name), position(position), rotation(rotation)
{

}

void Unit::setName(const std::string &name)
{
  this->name = name;
}

void Unit::setPosition(sf::Vector2f position)
{
  this->position = position;
}

void Unit::setRotation(sf::Vector2f rotation)
{
  if (std::fabs(rotation.x) < 1e-5 && std::fabs(rotation.y) < 1e-5)
  {
    return;
  }

  this->rotation = rotation;
}

std::string Unit::getName() const
{
  return name;
}

sf::Vector2f Unit::getPosition() const
{
  return position;
}

sf::Vector2f Unit::getRotation() const
{
  return rotation;
}

PlayerUnit::PlayerUnit(const std::string& name, sf::Vector2f position, sf::Vector2f rotation)
: Unit(name, position, rotation)
{
  player.setRadius(30.0);
  player.setFillColor(sf::Color(0, 255, 0, 255));
  gun.setPointCount(3);
  gun.setFillColor(sf::Color(255, 0, 0, 255));
}

PlayerUnit::~PlayerUnit()
{
}

void PlayerUnit::update()
{
  player.setPosition(getPosition() - sf::Vector2f(player.getRadius(), player.getRadius()));

  float length = getRotation().x * getRotation().x +
    getRotation().y * getRotation().y;

  length = sqrt(length);

  sf::Vector2f v = (player.getRadius() / length) * getRotation();
  sf::Vector2f n(-v.y, v.x);
  n = static_cast<float> (0.3) * n;

  gun.setPoint(0, getPosition());
  gun.setPoint(1, getPosition() + v + n);
  gun.setPoint(2, getPosition() + v - n);
}

void PlayerUnit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(player, states);
  target.draw(gun, states);
}

}

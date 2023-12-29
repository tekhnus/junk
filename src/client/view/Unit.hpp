#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


namespace junk
{

class Unit : public sf::Drawable
{
public:
  explicit Unit(const std::string& name = "", sf::Vector2f position = sf::Vector2f(0.0, 0.0),
                sf::Vector2f rotation = sf::Vector2f(1.0, 1.0));

  virtual ~Unit()
  {
  }

  void setName(const std::string &name);
  void setPosition(sf::Vector2f position);
  void setRotation(sf::Vector2f rotation);

  std::string getName() const;
  sf::Vector2f getPosition() const;
  sf::Vector2f getRotation() const;

  virtual void update() = 0;

private:
  std::string name;
  sf::Vector2f position;
  sf::Vector2f rotation;

};

class PlayerUnit : public Unit
{
public:
  explicit PlayerUnit(const std::string& name = "", sf::Vector2f position = sf::Vector2f(0.0, 0.0),
                      sf::Vector2f rotation = sf::Vector2f(1.0, 1.0));
  virtual ~PlayerUnit();
  void update();

private:
  sf::CircleShape player;
  sf::ConvexShape gun;

protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

}

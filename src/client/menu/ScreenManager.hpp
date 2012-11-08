#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

namespace junk
{

class ScreenManager : public sf::Drawable
{
public:
  void setView(sf::Drawable& target);
protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
  std::shared_ptr<sf::Drawable> vi;
};

}
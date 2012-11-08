#include "ScreenManager.hpp"

namespace junk
{

void ScreenManager::setView(sf::Drawable& view)
{
  vi = std::shared_ptr<sf::Drawable>(&view);
}

void ScreenManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  if (vi != nullptr)
    target.draw(*vi, states);
}

}
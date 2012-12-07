#include "Bonus.hpp"
#include "common/logger/Logger.hpp"

namespace junk {
namespace client {
namespace view {

VIEW_GAME_OBJECT_IMPL(Bonus, bonus, BONUS)

Bonus::Bonus()
{
    body.setRadius(10);
    body.setFillColor(sf::Color::Red);
    body.setOutlineThickness(0.0);
    body.setOrigin(sf::Vector2f(body.getRadius(), body.getRadius()));
}

Bonus::~Bonus()
{
}

void Bonus::updateBonus(const model::Bonus& bonus)
{
    position = bonus.position;
    body.setPosition(position * 20.0f);
    bonusType = bonus.bonusType;

    switch (bonusType)
    {
    case 0: // Health
        body.setFillColor(sf::Color::Red);
        break;
    case 1: // Speed
        body.setFillColor(sf::Color::Blue);
        break;
    }

    if (bonus.destroyInfo.isDestructing)
    {
      destroyInfo.isDestructing = true;
      destroyInfo.destroyCountdown = bonus.destroyInfo.destroyCountdown;
    }
}

void Bonus::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(body, states);
}

}}} // namespace junk::client::view


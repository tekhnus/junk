#include "Bonus.hpp"

namespace junk {
namespace client {
namespace view {

VIEW_GAME_OBJECT_IMPL(Bonus, bonus, BONUS)

Bonus::Bonus()
{
    body.setRadius(5);
    body.setFillColor(sf::Color::Red);
    body.setOutlineColor(sf::Color::Red);
    body.setOrigin(sf::Vector2f(body.getRadius(), body.getRadius()));
}

Bonus::~Bonus()
{
}

void Bonus::updateBonus(const model::Bonus& bonus)
{
    position = bonus.position;
    body.setPosition(position);

    if (bonus.destroyInfo.isDestroyed)
    {
      destroyInfo.isDestroyed = true;
      destroyInfo.destroyCountdown = bonus.destroyInfo.destroyCountdown;
    }
}

void Bonus::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(body, states);
}

}}} // namespace junk::client::view


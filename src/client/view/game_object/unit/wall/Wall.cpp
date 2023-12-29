#include "Wall.hpp"

namespace junk {
namespace client {
namespace view {

VIEW_GAME_OBJECT_IMPL(Wall, wall, WALL)

Wall::Wall() {
  body.setFillColor(sf::Color::White);
}

Wall::~Wall() {}

void Wall::updateWall(const model::Wall& wall) {
  body.setPointCount(wall.corners.size());
  for (size_t i = 0; i < wall.corners.size(); ++i) {
    body.setPoint(i, wall.corners[i]);
  }
}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(body, states);
}

}  // namespace view
}  // namespace client
}  // namespace junk

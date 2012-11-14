#include "Convert.hpp"

namespace junk {
namespace common {

sf::Vector2f to_SFML_Vector2f(const Vector2f& v)
{
  return sf::Vector2f(v.x, v.y);
}

Vector2f to_thrift_Vector2f(const sf::Vector2f& v)
{
  Vector2f u;
  u.x = v.x;
  u.y = v.y;
  return u;
}

}} // namespace junk::common

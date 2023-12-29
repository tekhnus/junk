#pragma once

#include <gen-cpp/ServiceDefinition_types.h>

#include <SFML/System.hpp>

namespace junk {
namespace common {

sf::Vector2f to_SFML_Vector2f(const Vector2f& v);
Vector2f to_thrift_Vector2f(const sf::Vector2f& v);

}  // namespace common
}  // namespace junk

#pragma once

#include <SFML/System.hpp>
#include <cstdint>

namespace junk {
namespace common {

class GameObject
{
public:
  GameObject();
  virtual ~GameObject();

  struct DestroyInfo
  {
    bool isDestroyed;
    int32_t destroyCountdown;
  };

  int32_t id;

  DestroyInfo destroyInfo;

}; // GameObject

}} // namespace junk::common

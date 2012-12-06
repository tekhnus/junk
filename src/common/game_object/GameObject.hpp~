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
    bool isDestructing;
    int32_t destroyCountdown;
  };

  bool isDestroyed() const;

  int32_t id;

  DestroyInfo destroyInfo;

}; // GameObject

}} // namespace junk::common

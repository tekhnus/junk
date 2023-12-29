#pragma once

#include <box2d/b2_world_callbacks.h>

#include <common/logger/Logger.hpp>

namespace junk {
namespace server {
namespace model {

class CollisionHandler : public b2ContactListener {
 public:
  void BeginContact(b2Contact* contact);

};  // CollisionHandler

}  // namespace model
}  // namespace server
}  // namespace junk

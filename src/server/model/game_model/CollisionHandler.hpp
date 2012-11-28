#pragma once

#include <common/logger/Logger.hpp>

#include "ServerGameModel.hpp"

namespace junk {
namespace server {
namespace model {

class CollisionHandler : public b2ContactListener
{
public:
  void BeginContact(b2Contact* contact);
  
}; // CollisionHandler

}}} // namespace junk::server::model

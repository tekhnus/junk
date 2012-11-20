#pragma once

#include "server/model/ServerModel.hpp"

namespace junk {
namespace server {

class Server
{
public:
  Server();

  void run();

private:
  model::ServerModel model;

}; // Server

}} // namespace junk::server

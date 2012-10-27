#pragma once

#include "server/model/ServerModel.hpp"

namespace junk
{

class Server
{
public:
  Server();

  void run();

private:
  ServerModel model;

}; // Server

} // namespace junk
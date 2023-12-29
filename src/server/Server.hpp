#pragma once

#include "server/model/ServerModel.hpp"

namespace junk {
namespace server {

class Server {
 public:
  Server();

  void run();

  void join();

 private:
  model::ServerModel model;

};  // Server

}  // namespace server
}  // namespace junk

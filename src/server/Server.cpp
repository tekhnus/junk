#include "Server.hpp"


namespace junk {
namespace server {

Server::Server()
{
}

void Server::run()
{
  model.start();
}

}} // namespace junk::server

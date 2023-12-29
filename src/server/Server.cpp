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

void Server::join()
{
  model.join();
}

}} // namespace junk::server

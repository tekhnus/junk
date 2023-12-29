#include "server/Server.hpp"
#include "common/utils/Resource.hpp"
#include "libgen.h"


int main(int , char **argv)
{
  resource_root = std::string(dirname(dirname(argv[0]))) + "/share/junk";
  junk::server::Server server;
  server.run();
  server.join();
  return 0;
}

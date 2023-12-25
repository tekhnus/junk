#include "server/Server.hpp"
#include "common/utils/Resource.hpp"
#include "libgen.h"

#include <iostream>

int main(int argc, char **argv)
{
  resource_root = std::string(dirname(dirname(argv[0]))) + "/share/junk";
  junk::server::Server server;
  server.run();
  while (true)
  {

  }
  return 0;
}

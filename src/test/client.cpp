#include "client/Client.hpp"
#include "libgen.h"
#include <string>
#include "common/utils/Resource.hpp"

int main(int argc, char **argv)
{
  resource_root = std::string(dirname(dirname(argv[0]))) + "/share/junk";
  junk::Client client;
  client.connectToServer("localhost", 7777);
  while (true)
  {

  }
  return 0;
}

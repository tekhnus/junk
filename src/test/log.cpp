#include "common/logger/Logger.hpp"
#include <string>

using namespace junk;

int main()
{
  Logger log1("log1");
  Logger log2("log2");
  Logger log3("log3", "log.log");
  Logger log4("log4", "log.log", false);

  std::string message;
  while (std::getline(std::cin, message) && message != "exit")
  {
    log1.warn(message);
    log2.warn(message, " !! ", 42);
    log3.debug(message);
    log4.debug(message);
  }

  return 0;
}

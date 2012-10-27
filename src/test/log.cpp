#include "common/logger/Logger.hpp"
#include <string>

int main()
{
  Logger log1("log1");
  Logger log2("log2");
  Logger log3("log3", "log.txt");
  Logger log4("log4", "log.txt", false);
  log1.set(false);

  std::string message;
  while (std::getline(std::cin, message) && message != "exit")
  {
    log1 << message;
    log2 << message << "!!";
    log3 << message;
    log4 << message;
  }

  return 0;
}

#include "Logger.hpp"
#include <mutex>

namespace junk
{

Logger dbg("debug", "debug.log");

static unsigned globalCount = 0;

static unsigned nextColor()
{
  return 31 + globalCount++ % 7;
}

Logger::Logger(const std::string& title,
               const std::string& filename, bool verbose)
: file(filename.c_str(), std::ios::app), title(title),
color(nextColor()), verbose(verbose)
{
	settings.load("/tmp/logger_config.json");
}

Logger::Logger(const std::string& title)
: title(title), color(nextColor()), verbose(true)
{
	settings.load("/tmp/logger_config.json");
}

Logger::~Logger()
{
  if (file.is_open())
  {
    file.close();
  }
}

void Logger::writeHead(std::ostream& stream, bool colored, bool dated)
{
  if (dated)
  {
    time_t logTime = std::time(nullptr);
    std::string reprTime(std::asctime(std::localtime(&logTime)));
    stream << reprTime;
  }
  if (colored)
  {
    stream << "\x1b[4m\x1b[" << color << "m" << title << ":" << "\x1b[0m ";
  }
  else
  {
    stream << title << ": ";
  }
}

void Logger::_log(int )
{}

}

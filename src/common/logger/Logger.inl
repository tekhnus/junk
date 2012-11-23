#include <mutex>

namespace junk
{

static std::mutex safelog;

template<typename ... T>
void Logger::warn(const T& ... message)
{
	log(LEVEL_WARN, message ...);
}

template<typename ... T>
void Logger::debug(const T& ... message)
{
	log(LEVEL_DEBUG, message ...);
}

template<typename F, typename ... T>
void Logger::_log(int level, const F& first, const T& ... message)
{
  if (verbose)
  {
    std::cerr << first;
  }
  if (file.is_open())
  {
    file << first;
  }

  _log(level, message ...);
}

template<typename F, typename ... T>
void Logger::log(int level, const F& first, const T& ... message)
{
	if (level > settings.level)
	{
		return;
	}
	std::lock_guard<std::mutex> lock(safelog);
	if (verbose)
  {
    writeHead(std::cerr, true, false);
  }
  if (file.is_open())
  {
    writeHead(file, false, true);
  }
	_log(level, first, message ..., "\n");
}

template<typename T>
Logger& Logger::operator<<(const T &message)
{
  log(LEVEL_DEBUG, message);
  return *this;
}

}
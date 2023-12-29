#pragma once

#include "Settings.hpp"

#include <fstream>
#include <iostream>

namespace junk
{

class Logger
{
public:
  explicit Logger(const std::string& title, const std::string& filename, bool verbose = true);
  explicit Logger(const std::string& title);
  ~Logger();

  template<typename T>
  Logger& operator<<(const T& message);

  template<typename ... T>
  void warn(const T& ... message);

  template<typename ... T>
  void debug(const T& ... message);

private:
	void _log(int level);

	template<typename F, typename ... T>
	void _log(int level, const F& first, const T& ... message);

	template<typename F, typename ... T>
	void log(int level, const F& first, const T& ... message);

  void writeHead(std::ostream& stream, bool colored, bool dated);

  std::ofstream file;
  std::string title;
  unsigned color;
  bool verbose;
  Settings settings;
};

extern Logger dbg;

} // junk

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

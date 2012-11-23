#pragma once

#include "Settings.hpp"

#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <utility>
#include <memory>

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

} // junk

#include "Logger.inl"

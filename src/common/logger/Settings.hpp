#pragma once

#include <string>

namespace junk
{

extern int LEVEL_NONE;
extern int LEVEL_WARN;
extern int LEVEL_DEBUG;

struct Settings
{
  int level;

  void load(std::string file);
  void save(std::string file);
};

}
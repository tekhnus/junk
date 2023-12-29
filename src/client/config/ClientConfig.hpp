#pragma once

#include <list>
#include <string>

namespace junk {

struct ClientConfig {
  std::list<std::string> recent;
  std::string name;
  void load(std::string file);
  void save(std::string file);
};

}  // namespace junk
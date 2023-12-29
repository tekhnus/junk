#include "Settings.hpp"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace junk {

int LEVEL_NONE = 1;
int LEVEL_WARN = 2;
int LEVEL_DEBUG = 3;

using boost::property_tree::ptree;

void Settings::load(std::string filename) {
  ptree tree;
  try {
    read_json(filename, tree);
    level = tree.get<int>("level");
  } catch (std::exception ex) {
    level = LEVEL_DEBUG;
    save(filename);
  }
}

void Settings::save(std::string filename) {
  ptree tree;
  tree.add("level", level);
  write_json(filename, tree);
}

}  // namespace junk

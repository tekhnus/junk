#include "ClientConfig.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;

namespace junk
{
  void ClientConfig::load(std::string filename) {
    ptree tree;
    read_json(filename, tree);
    for (auto& entry : tree.get_child("recent")) {
      recent.push_back(entry.second.data());
    }
  } 

  void ClientConfig::save(std::string filename) {
    ptree tree;
    for (auto& entry : recent) {
      tree.add("recent.address", entry);
    }
    write_json(filename, tree);
  } 
}
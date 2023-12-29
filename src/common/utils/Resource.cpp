#include "Resource.hpp"

#include <cstdlib>
#include <iostream>

std::string resource_root = "";

std::string get_resource_path(std::string resource_name) {
  std::cerr << "Getting resource " << resource_name << std::endl;
  std::cerr << "(2) Resource root is " << resource_root << std::endl;
  const char* resource_dir = getenv("JUNK_RESOURCE_DIR");
  if (resource_dir == nullptr) {
    resource_dir = resource_root.c_str();
  }
  return std::string{resource_dir} + "/" + resource_name;
}

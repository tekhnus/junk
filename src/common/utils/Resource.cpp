#include "Resource.hpp"

std::string resource_root = "";

std::string get_resource_path(std::string resource_name) {
  return resource_root + "/" + resource_name;
}

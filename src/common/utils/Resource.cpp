#include "Resource.hpp"
#include <cstdlib>


std::string get_resource_path(std::string resource_name) {
    const char* resource_dir;
    if ((resource_dir = getenv("JUNK_RESOURCE_DIR")) == nullptr) {
        resource_dir = "/usr/local/share";
    }
    return (std::string)resource_dir + "/" + resource_name;
}

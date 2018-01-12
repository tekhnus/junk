cmake_minimum_required (VERSION 3.1)

project (junk CXX)
set (CMAKE_CXX_STANDARD 11)

add_definitions (-DHAVE_NETINET_IN_H)
add_definitions (-DHAVE_CONFIG_H)

add_subdirectory (src build)

install (FILES arial.ttf Theme.theme map.json DESTINATION share/junk)

set (CPACK)
set (CPACK_GENERATOR "DEB")
set (CPACK_DEBIAN_PACKAGE_MAINTAINER "Junk Team")

include (CPack)

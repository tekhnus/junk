cmake_minimum_required (VERSION 2.6)

project (junk CXX)

set (CMAKE_CXX_COMPILER g++-4.8)
add_definitions (-std=c++11 -g)

include_directories (/usr/include/sigc++-2.0)
include_directories (/usr/lib/x86_64-linux-gnu/sigc++-2.0/include)

include_directories (/usr/include/thrift/)

add_definitions (-DHAVE_NETINET_IN_H)
add_definitions (-DHAVE_CONFIG_H)

link_directories (/opt/lib)

add_subdirectory (src build)

install (FILES arial.ttf Theme.theme map.json DESTINATION share/junk)

set (CPACK)
set (CPACK_GENERATOR "DEB")
set (CPACK_DEBIAN_PACKAGE_MAINTAINER "Junk Team")

include (CPack)

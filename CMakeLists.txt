cmake_minimum_required (VERSION 2.6)

project (junk CXX)

set (CMAKE_CXX_COMPILER g++-4.8)
add_definitions (-std=c++11)

include_directories (/usr/include/sigc++-2.0)
include_directories (/usr/lib/x86_64-linux-gnu/sigc++-2.0/include)

include_directories (/usr/local/include/thrift/)

add_definitions (-DHAVE_NETINET_IN_H)
add_definitions (-DHAVE_CONFIG_H)

add_subdirectory (src build)

set (CPACK)
set (CPACK_GENERATOR "DEB")
set (CPACK_DEBIAN_PACKAGE_MAINTAINER "Junk Team")
set (LIB_PREF /usr/local/lib)
install (FILES arial.ttf Theme.theme DESTINATION share/junk)
include (CPack)


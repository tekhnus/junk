cmake_minimum_required (VERSION 2.6)

project (junk CXX)

add_definitions (--std=c++0x)

IF(UNIX)
	include_directories (/usr/include/sigc++-2.0)
	include_directories (/usr/lib/x86_64-linux-gnu/sigc++-2.0/include)
ENDIF(UNIX)

IF(APPLE)
	include_directories (/opt/local/include/sigc++-2.0)
	include_directories (/opt/local/include)
	include_directories (/opt/local/include/thrift)
ENDIF(APPLE)

add_subdirectory (src build)

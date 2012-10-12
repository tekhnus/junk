cmake_minimum_required (VERSION 2.6)

project (junk CXX)

IF(APPLE)
	set (CMAKE_CXX_COMPILER clang++)
	set (CMAKE_EXE_LINKER_FLAGS -stdlib=libc++)
	add_definitions (-std=c++11)
	add_definitions (-stdlib=libc++)
	include_directories (/opt/local/include/sigc++-2.0)
	include_directories (/opt/local/include)
	include_directories (/opt/local/include/thrift)
ELSE(APPLE)
	add_definitions (-std=c++0x)
	include_directories (/usr/include/sigc++-2.0)
	include_directories (/usr/lib/x86_64-linux-gnu/sigc++-2.0/include)
ENDIF(APPLE)

add_subdirectory (src build)

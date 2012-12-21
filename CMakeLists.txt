cmake_minimum_required (VERSION 2.6)

project (junk CXX)

set (CMAKE_CXX_COMPILER g++-4.6)

IF(APPLE)
	#set (CMAKE_CXX_COMPILER clang++)
	#set (CMAKE_CXX_COMPILER g++)
	#set (CMAKE_EXE_LINKER_FLAGS -stdlib=libc++)
	add_definitions (-std=c++0x)
  add_definitions (-lGLEW)
	#add_definitions (-stdlib=libc++)
  include_directories (/opt/local/include/sigc++-2.0)
  include_directories (/opt/local/include)
  include_directories (/usr/local/include)
	#include_directories (/opt)
ELSE(APPLE)
	add_definitions (-std=c++0x)
  include_directories (/usr/include/sigc++-2.0)
  include_directories (/usr/lib/x86_64-linux-gnu/sigc++-2.0/include)
ENDIF(APPLE)


include_directories (/usr/local/include/thrift/)

add_definitions (-DHAVE_NETINET_IN_H)
add_definitions (-DHAVE_CONFIG_H)

add_subdirectory (src build)

set (CPACK)
set (CPACK_GENERATOR "DEB")
set (CPACK_DEBIAN_PACKAGE_MAINTAINER "Junk team")

set (LIB_PREF /usr/local/lib)
install (FILES arial.ttf Theme.theme DESTINATION share/junk)
install (FILES
    ${LIB_PREF}/libsfml-graphics.so ${LIB_PREF}/libsfml-window.so ${LIB_PREF}/libsfml-system.so
    ${LIB_PREF}/libsfml-graphics.so.2 ${LIB_PREF}/libsfml-window.so.2 ${LIB_PREF}/libsfml-system.so.2
    ${LIB_PREF}/libsfml-graphics.so.2.0 ${LIB_PREF}/libsfml-window.so.2.0 ${LIB_PREF}/libsfml-system.so.2.0
    ${LIB_PREF}/libsfgui.so ${LIB_PREF}/libthrift-0.9.0-dev.so ${LIB_PREF}/libBox2D.so ${LIB_PREF}/libBox2D.so.2.1.0 DESTINATION local/lib)

include (CPack)

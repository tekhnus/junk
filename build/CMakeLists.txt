cmake_minimum_required (VERSION 2.6)
project (junk)

set (SRC ../src)
set (BIN ../bin)

add_definitions (-std=c++0x)

include_directories (${SRC})

include_directories (/usr/include/sigc++-2.0)
include_directories (/usr/lib/x86_64-linux-gnu/sigc++-2.0/include)

add_executable (${BIN}/client ${SRC}/test/client.cpp ${SRC}/client/Client.cpp ${SRC}/common/logger/Logger.cpp)
add_executable (${BIN}/server ${SRC}/test/server.cpp ${SRC}/server/Server.cpp ${SRC}/common/logger/Logger.cpp)
add_executable (${BIN}/view ${SRC}/test/view.cpp ${SRC}/client/view/unit/Unit.cpp)


target_link_libraries (${BIN}/client sfml-system)
target_link_libraries (${BIN}/client sfml-network)
target_link_libraries (${BIN}/server sfml-system)
target_link_libraries (${BIN}/server sfml-network)
target_link_libraries (${BIN}/server sigc-2.0)
target_link_libraries (${BIN}/view sfml-system)
target_link_libraries (${BIN}/view sfml-network)
target_link_libraries (${BIN}/view sfml-window)
target_link_libraries (${BIN}/view sfml-graphics)

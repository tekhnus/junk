cmake_minimum_required(VERSION 3.13)
project(junk CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Boost 1.74 REQUIRED)
find_package(SFML 2.5.1 REQUIRED COMPONENTS system)
find_package(box2d 2.4.0 EXACT REQUIRED)
# FIXME Write a nice Thrift CMake config file instead of FindThift.cmake
find_package(Thrift 0.13 EXACT REQUIRED)
# FIXME Get rid of explicit transitive dependency (libevent) configuration
find_package(Libevent 2.1.12 EXACT REQUIRED)

add_executable(server "")

# FIXME Separate the commands
# FIXME Do not hardcode Thrift compiler path
add_custom_command(
	OUTPUT gen/gen-cpp/ServiceDefinition_types.cpp gen/gen-cpp/ClientService.cpp gen/gen-cpp/Actions_types.cpp gen/gen-cpp/Patches_types.cpp gen/gen-cpp/Shared_types.cpp gen/gen-cpp/ClientService.h
	COMMAND mkdir -p ${PROJECT_BINARY_DIR}/gen
	COMMAND /Users/harius/env/junk/usr/bin/thrift --gen cpp -o ${PROJECT_BINARY_DIR}/gen ${CMAKE_CURRENT_SOURCE_DIR}/src/common/service/Shared.thrift
	COMMAND /Users/harius/env/junk/usr/bin/thrift --gen cpp -o ${PROJECT_BINARY_DIR}/gen ${CMAKE_CURRENT_SOURCE_DIR}/src/common/service/Patches.thrift
	COMMAND /Users/harius/env/junk/usr/bin/thrift --gen cpp -o ${PROJECT_BINARY_DIR}/gen ${CMAKE_CURRENT_SOURCE_DIR}/src/common/service/Actions.thrift
	COMMAND /Users/harius/env/junk/usr/bin/thrift --gen cpp -o ${PROJECT_BINARY_DIR}/gen ${CMAKE_CURRENT_SOURCE_DIR}/src/common/service/ServiceDefinition.thrift
	COMMENT "Thrifting service" 
)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/gen)
target_sources(server
	PRIVATE
		${PROJECT_BINARY_DIR}/gen/gen-cpp/ServiceDefinition_types.cpp
		${PROJECT_BINARY_DIR}/gen/gen-cpp/ClientService.cpp
		${PROJECT_BINARY_DIR}/gen/gen-cpp/Actions_types.cpp
		${PROJECT_BINARY_DIR}/gen/gen-cpp/Patches_types.cpp
		${PROJECT_BINARY_DIR}/gen/gen-cpp/Shared_types.cpp
)

target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
# FIXME The include paths should be propagated by target_link_libraries(...)
target_include_directories(server PRIVATE ${THRIFT_INCLUDE_DIR})
target_compile_features(server PRIVATE cxx_std_11)

# FIXME Get rid of explicit transitive dependency (libevent) configuration
target_link_libraries(server sfml-system ${THRIFT_STATIC_LIB} box2d::box2d /Users/harius/env/junk/usr/lib/libthriftnb.a libevent::core)

add_subdirectory(src)

cmake_minimum_required(VERSION 3.13)
project(junk CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Boost 1.74 REQUIRED)
find_package(SFML 2.5.1 REQUIRED COMPONENTS system graphics)
# TODO Write a nice SFGUI config file instead of FindSFGUI.cmake
find_package(SFGUI 0.4.0 EXACT REQUIRED)
find_package(box2d 2.4.0 EXACT REQUIRED)
find_package(Thrift 0.13.0 EXACT REQUIRED)

# TODO Report the bug in https://github.com/apache/thrift/blob/0.13.0/build/cmake/ThriftConfig.cmake.in to Thrift developers.
include("${THRIFT_CMAKE_DIR}/thriftnbTargets.cmake")
# TODO The emptiness of the THRIFT_COMPILER variable is also a bug.
set(THRIFT_COMPILER "${THRIFT_BIN_DIR}/thrift")

add_executable(server "")
add_executable(client "")


# FIXME Separate the commands
add_custom_command(
	OUTPUT gen/gen-cpp/ServiceDefinition_types.cpp gen/gen-cpp/ClientService.cpp gen/gen-cpp/Actions_types.cpp gen/gen-cpp/Patches_types.cpp gen/gen-cpp/Shared_types.cpp gen/gen-cpp/ClientService.h
	COMMAND mkdir -p ${PROJECT_BINARY_DIR}/gen
    COMMAND "${THRIFT_COMPILER}" --gen cpp -o ${PROJECT_BINARY_DIR}/gen ${CMAKE_CURRENT_SOURCE_DIR}/src/common/service/Shared.thrift
    COMMAND "${THRIFT_COMPILER}" --gen cpp -o ${PROJECT_BINARY_DIR}/gen ${CMAKE_CURRENT_SOURCE_DIR}/src/common/service/Patches.thrift
    COMMAND "${THRIFT_COMPILER}" --gen cpp -o ${PROJECT_BINARY_DIR}/gen ${CMAKE_CURRENT_SOURCE_DIR}/src/common/service/Actions.thrift
    COMMAND "${THRIFT_COMPILER}" --gen cpp -o ${PROJECT_BINARY_DIR}/gen ${CMAKE_CURRENT_SOURCE_DIR}/src/common/service/ServiceDefinition.thrift
	COMMENT "Thrifting service" 
)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/gen)
target_include_directories(client PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/gen)

target_sources(server
	PRIVATE
		${PROJECT_BINARY_DIR}/gen/gen-cpp/ServiceDefinition_types.cpp
		${PROJECT_BINARY_DIR}/gen/gen-cpp/ClientService.cpp
		${PROJECT_BINARY_DIR}/gen/gen-cpp/Actions_types.cpp
		${PROJECT_BINARY_DIR}/gen/gen-cpp/Patches_types.cpp
		${PROJECT_BINARY_DIR}/gen/gen-cpp/Shared_types.cpp
)
target_sources(client
	PRIVATE
		${PROJECT_BINARY_DIR}/gen/gen-cpp/ServiceDefinition_types.cpp
		${PROJECT_BINARY_DIR}/gen/gen-cpp/ClientService.cpp
		${PROJECT_BINARY_DIR}/gen/gen-cpp/Actions_types.cpp
		${PROJECT_BINARY_DIR}/gen/gen-cpp/Patches_types.cpp
		${PROJECT_BINARY_DIR}/gen/gen-cpp/Shared_types.cpp
)

target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)


target_compile_features(server PRIVATE cxx_std_11)
target_compile_features(client PRIVATE cxx_std_11)

target_link_libraries(server sfml-system thrift::thrift thriftnb::thriftnb box2d::box2d)
target_link_libraries(client sfml-system sfml-graphics thrift::thrift thriftnb::thriftnb box2d::box2d ${SFGUI_LIBRARY})

# TODO After the removal of FindSFGUI.cmake, this explicit include dir configuration can be dropped.
target_include_directories(client PRIVATE ${SFGUI_INCLUDE_DIR})

add_subdirectory(src)

cmake_minimum_required(VERSION 3.13)
project(junk CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Boost 1.74 REQUIRED)
find_package(SFML 2.5.1 REQUIRED COMPONENTS system graphics)
# TODO Write a nice SFGUI config file instead of FindSFGUI.cmake
find_package(SFGUI 0.4.0 EXACT REQUIRED)
find_package(box2d 2.4.1 EXACT REQUIRED)
find_package(Thrift 0.15.0 EXACT REQUIRED)

# TODO Report the bug in https://github.com/apache/thrift/blob/0.13.0/build/cmake/ThriftConfig.cmake.in to Thrift developers.
include("${THRIFT_CMAKE_DIR}/thriftnbTargets.cmake")
# TODO The emptiness of the THRIFT_COMPILER variable should also be reported as a bug.
set(THRIFT_COMPILER "${THRIFT_BIN_DIR}/thrift")

add_executable(server "")
add_executable(client "")

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/gen)

target_include_directories(server PRIVATE ${PROJECT_BINARY_DIR}/gen)
target_include_directories(client PRIVATE ${PROJECT_BINARY_DIR}/gen)

macro(add_thrift_rule)
    cmake_parse_arguments(ADD_THRIFT "" SOURCE OUTPUT ${ARGN})
    add_custom_command(
        OUTPUT ${ADD_THRIFT_OUTPUT}
        COMMAND "${THRIFT_COMPILER}" --gen cpp -o ${PROJECT_BINARY_DIR}/gen ${CMAKE_CURRENT_SOURCE_DIR}/${ADD_THRIFT_SOURCE}
    )
endmacro()

add_thrift_rule(
        OUTPUT gen/gen-cpp/Shared_types.cpp
        SOURCE src/common/service/Shared.thrift
)
add_thrift_rule(
        OUTPUT gen/gen-cpp/Patches_types.cpp
        SOURCE src/common/service/Patches.thrift
)
add_thrift_rule(
        OUTPUT gen/gen-cpp/Actions_types.cpp
        SOURCE src/common/service/Actions.thrift
)
add_thrift_rule(
        OUTPUT gen/gen-cpp/ServiceDefinition_types.cpp gen/gen-cpp/ClientService.cpp
        SOURCE src/common/service/ServiceDefinition.thrift
)

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

set_target_properties(server PROPERTIES
    RESOURCE
        resources/map.json
)
set_target_properties(client PROPERTIES
    RESOURCE
        "resources/arial.ttf;resources/Theme.theme"
)
install(TARGETS server client RESOURCE DESTINATION share/junk)

add_custom_target(run-server
    COMMAND JUNK_RESOURCE_DIR=${PROJECT_SOURCE_DIR}/resources ./server
    DEPENDS server
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
add_custom_target(run-client
    COMMAND JUNK_RESOURCE_DIR=${PROJECT_SOURCE_DIR}/resources ./client
    DEPENDS client
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)

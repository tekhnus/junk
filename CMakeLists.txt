cmake_minimum_required(VERSION 3.13)
project(junk CXX)
find_package(PkgConfig REQUIRED)

find_package(Boost 1.77.0 EXACT REQUIRED NO_MODULE)
find_package(SFML 2.5.1 EXACT REQUIRED COMPONENTS system graphics NO_MODULE)
find_package(SFGUI 0.4.0 EXACT REQUIRED NO_MODULE)
find_package(box2d 2.4.1 EXACT REQUIRED NO_MODULE)

pkg_check_modules(libevent REQUIRED IMPORTED_TARGET libevent)
add_library(libevent::libevent ALIAS PkgConfig::libevent)

pkg_check_modules(thrift REQUIRED IMPORTED_TARGET thrift)
add_library(thrift::thrift ALIAS PkgConfig::thrift)
pkg_check_modules(thriftnb REQUIRED IMPORTED_TARGET thrift-nb)
add_library(thriftnb::thriftnb ALIAS PkgConfig::thriftnb)
find_program(THRIFT_COMPILER thrift REQUIRED)

add_executable(server "")
add_executable(client "")

file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/gen)

target_include_directories(server PRIVATE ${PROJECT_BINARY_DIR}/gen)
target_include_directories(client PRIVATE ${PROJECT_BINARY_DIR}/gen)

macro(add_thrift_rule)
    cmake_parse_arguments(ADD_THRIFT "" SOURCE OUTPUT ${ARGN})
    add_custom_command(
        OUTPUT ${ADD_THRIFT_OUTPUT}
        COMMAND echo  "${THRIFT_COMPILER}" --gen cpp -o ${PROJECT_BINARY_DIR}/gen ${CMAKE_CURRENT_SOURCE_DIR}/${ADD_THRIFT_SOURCE}
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

target_link_libraries(server sfml-system thrift::thrift thriftnb::thriftnb box2d::box2d pthread rt libevent::libevent)
target_link_libraries(client sfml-system sfml-graphics thrift::thrift thriftnb::thriftnb box2d::box2d SFGUI::SFGUI)

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

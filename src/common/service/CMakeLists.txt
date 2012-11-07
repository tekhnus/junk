add_custom_command(
OUTPUT gen-cpp/ServiceDefinition_types.cpp gen-cpp/ClientService.cpp
COMMAND thrift --gen cpp ${CMAKE_CURRENT_SOURCE_DIR}/Shared.thrift
COMMAND thrift --gen cpp ${CMAKE_CURRENT_SOURCE_DIR}/Patches.thrift
COMMAND thrift --gen cpp ${CMAKE_CURRENT_SOURCE_DIR}/Actions.thrift
COMMAND thrift --gen cpp ${CMAKE_CURRENT_SOURCE_DIR}/ServiceDefinition.thrift
COMMENT "Thrifting service" 
)

#include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library (clientservicehandler gen-cpp/ServiceDefinition_types.cpp gen-cpp/ClientService.cpp client/ClientServiceHandler.cpp gen-cpp/Actions_types.cpp gen-cpp/Patches_types.cpp gen-cpp/Shared_types.cpp)

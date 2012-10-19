add_custom_command(
OUTPUT gen-cpp/ClientService.h
COMMAND thrift --gen cpp ${CMAKE_CURRENT_SOURCE_DIR}/ServiceDefinition.thrift
COMMENT "Thrifting service" 
)

#include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library (clientservicehandler gen-cpp/ServiceDefinition_types.cpp gen-cpp/ClientService.cpp client/ClientServiceHandler.cpp)

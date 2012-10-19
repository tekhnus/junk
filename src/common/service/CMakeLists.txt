add_custom_command(
OUTPUT gen-cpp/ClientService.h gen-cpp/ServerService.h
COMMAND thrift --gen cpp ${CMAKE_CURRENT_SOURCE_DIR}/ServiceDefinition.thrift
COMMENT "Thrifting service" 
)

#include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library (clientservicehandler client/ClientServiceHandler.cpp gen-cpp/ClientService.h)
add_library (serverservicehandler server/ServerServiceHandler.cpp gen-cpp/ServerService.h)

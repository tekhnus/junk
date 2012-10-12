add_custom_command (
OUTPUT gen-cpp/ServerService.h
COMMAND thrift --gen cpp ${CMAKE_CURRENT_SOURCE_DIR}/ServerServiceDefinition.thrift
COMMENT "Thrifting server service" 
)

include_directories (${CMAKE_CURRENT_BINARY_DIR})
add_library (serverservicehandler ServerServiceHandler.cpp gen-cpp/ServerService.h)
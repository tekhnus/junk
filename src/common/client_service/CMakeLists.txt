add_custom_command(
OUTPUT gen-cpp
COMMAND thrift --gen cpp ${CMAKE_CURRENT_SOURCE_DIR}/ClientServiceDefinition.thrift
COMMENT "Thrifting client service" 
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_library (clientservicehandler ClientServiceHandler.cpp gen-cpp)
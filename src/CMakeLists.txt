include_directories(.)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/common/service)

add_subdirectory (common)
add_subdirectory (client)
add_subdirectory (server)
add_subdirectory (test)

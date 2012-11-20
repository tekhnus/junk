include_directories (${CMAKE_SOURCE_DIR}/build/common/server_service)

add_library (clientmodel ClientModel.cpp)
add_subdirectory (network_model)
add_subdirectory (game_object)
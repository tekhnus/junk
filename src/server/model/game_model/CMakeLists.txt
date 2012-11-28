add_library (servergamemodel ServerGameModel.cpp)

add_subdirectory (game_object)

add_library (collisionhandler CollisionHandler.cpp)
target_link_libraries (servergamemodel collisionhandler)


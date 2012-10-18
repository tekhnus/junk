add_library (unitservermodel Unit.cpp)
add_library (servergamemodel ServerGameModel.cpp)
target_link_libraries (servergamemodel unitservermodel)

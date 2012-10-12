add_executable (log log.cpp)
target_link_libraries(log logger sfml-system)

add_executable (view view.cpp)
target_link_libraries(view unit sfml-system sfml-window sfml-graphics)
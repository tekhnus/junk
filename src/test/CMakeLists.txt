add_executable (log log.cpp)
target_link_libraries(log logger)

add_executable (view view.cpp)
target_link_libraries(view unitview sfml-system sfml-window sfml-graphics)

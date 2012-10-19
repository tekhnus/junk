add_executable (log log.cpp)
target_link_libraries(log logger sfml-system)

add_executable (view view.cpp)
target_link_libraries(view unitview clientview clientmodel logger clientcontroller sfml-graphics sfml-window sfml-system sigc-2.0 pthread)

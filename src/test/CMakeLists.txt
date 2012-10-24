add_executable (log log.cpp)
target_link_libraries(log logger)

add_executable (view view.cpp)
target_link_libraries(view unitview clientview clientmodel clientnetworkmodel clientservicehandler logger clientcontroller sfml-graphics sfml-window sfml-system sigc-2.0 pthread thrift)

add_executable (servertest server.cpp)
target_link_libraries(servertest server servermodel servernetworkmodel servergamemodel unitservermodel clientservicehandler logger sfml-graphics sfml-window sfml-system sigc-2.0 pthread thrift)

add_executable (clienttest client.cpp)
target_link_libraries(clienttest client clientview unitview clientmodel clientnetworkmodel clientservicehandler logger clientcontroller sfml-graphics sfml-window sfml-system sigc-2.0 pthread thrift)

add_executable (log log.cpp)
target_link_libraries(log logger)

add_executable (view view.cpp)
target_link_libraries(view clientview clientmodel clientmodelgameobjectfactory
                      clientviewgameobjectfactory
                      clientviewplayer clientviewunit clientviewgameobject
                      clientmodelplayer clientmodelunit clientmodelgameobject
                      commonplayer commonunit commongameobject
                      clientnetworkmodel clientservicehandler logger utils
                      sfml-graphics sfml-window sfml-system pthread thrift)

add_executable (servertest server.cpp)
target_link_libraries(servertest server servermodel servernetworkmodel servergamemodel unitservermodel
                      servermodelplayer servermodelunit servermodelgameobject
                      commonplayer commonunit commongameobject clientservicehandler logger utils
                      sfml-graphics sfml-window sfml-system pthread thrift Box2D)

add_executable (clienttest client.cpp)
target_link_libraries(clienttest client clientview clientmodel
                      clientmodelgameobjectfactory
                      clientviewgameobjectfactory
                      clientviewplayer clientviewunit clientviewgameobject
                      clientmodelplayer clientmodelunit clientmodelgameobject
                      commonplayer commonunit commongameobject
                      clientnetworkmodel clientservicehandler logger utils
                      sfml-graphics sfml-window sfml-system pthread thrift)

add_executable (log log.cpp)
target_link_libraries (log logger)

add_executable (view view.cpp)
target_link_libraries(view clientview clientmodel clientmodelgameobjectfactory
                      clientviewgameobjectfactory clientviewbullet 
                      clientviewplayer clientviewunit clientviewgameobject
                      clientmodelbullet clientmodelplayer clientmodelunit clientmodelgameobject
                      commonbullet commonplayer commonunit commongameobject
                      clientnetworkmodel clientservicehandler logger utils
                      sfml-graphics sfml-window sfml-system pthread thrift
                      sfgui addressfetch clientconfig simplemenu)

add_executable (servertest server.cpp)
target_link_libraries(servertest server servermodel servernetworkmodel servergamemodel
                      servermodelbullet servermodelplayer servermodelunit servermodelgameobject
                      commonbullet commonplayer commonunit commongameobject clientservicehandler logger utils
                      sfml-graphics sfml-window sfml-system pthread thrift Box2D)

add_executable (clienttest client.cpp)
target_link_libraries(clienttest client clientview clientmodel
                      clientmodelgameobjectfactory
                      clientviewgameobjectfactory clientviewbullet
                      clientviewplayer clientviewunit clientviewgameobject
                      clientmodelbullet clientmodelplayer clientmodelunit clientmodelgameobject
                      commonbullet commonplayer commonunit commongameobject
                      clientnetworkmodel clientservicehandler logger utils
                      sfml-graphics sfml-window sfml-system pthread thrift)

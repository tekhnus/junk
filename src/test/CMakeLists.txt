add_executable (log log.cpp)
target_link_libraries (log logger)

add_executable (view view.cpp)
target_link_libraries(view clientview clientmodel clientmodelgameobjectfactory
                      clientviewgameobjectfactory clientviewwall clientviewbullet 
                      clientviewplayer clientviewunit clientviewgameobject
                      clientmodelwall clientmodelbullet clientmodelplayer clientmodelunit clientmodelgameobject
                      commonwall commonbullet commonplayer commonunit commongameobject
                      clientnetworkmodel clientservicehandler logger utils
                      sfml-graphics sfml-window sfml-system pthread thrift
                      sfgui addressfetch clientconfig simplemenu hud)

add_executable (servertest server.cpp)
target_link_libraries(servertest server servermodel servernetworkmodel servergamemodel servermodelwall
                      servermodelplayer servermodelbullet servermodelunit servermodelgameobject commonwall
                      commonbullet commonplayer commonunit commongameobject clientservicehandler logger utils
                      sfml-graphics sfml-window sfml-system pthread thrift Box2D)

add_executable (clienttest client.cpp)
target_link_libraries(clienttest client clientview clientmodel
                      clientmodelgameobjectfactory
                      clientviewgameobjectfactory clientviewbullet clientviewwall
                      clientviewplayer clientviewunit clientviewgameobject clientmodelwall
                      clientmodelbullet clientmodelplayer clientmodelunit clientmodelgameobject
                      commonwall commonbullet commonplayer commonunit commongameobject
                      clientnetworkmodel clientservicehandler logger utils
                      sfml-graphics sfml-window sfml-system pthread thrift)

add_executable (log log.cpp)
target_link_libraries (log logger)

add_executable (junk view.cpp)
target_link_libraries(junk clientview clientmodel clientmodelgameobjectfactory
                      clientviewgameobjectfactory clientviewbonus clientviewwall clientviewbullet 
                      clientviewplayer clientviewunit clientviewgameobject
                      clientmodelbonus clientmodelwall clientmodelbullet clientmodelplayer clientmodelunit clientmodelgameobject
                      commonbonus commonwall commonbullet commonplayer commonunit commongameobject
                      clientnetworkmodel clientservicehandler logger utils
                      sfml-graphics sfml-window sfml-system pthread thrift
                      sfgui addressfetch clientconfig simplemenu hud)

add_executable (servertest server.cpp)
target_link_libraries(servertest server servermodel servernetworkmodel servergamemodel servermodelbonus servermodelwall
                      servermodelplayer servermodelbullet servermodelunit servermodelgameobject commonbonus commonwall
                      commonbullet commonplayer commonunit commongameobject clientservicehandler logger utils
                      sfml-graphics sfml-window sfml-system pthread event thriftnb thrift event Box2D)

install (TARGETS junk servertest DESTINATION bin)


unset (SFML_GRAPHICS)
unset( SFML_WINDOW )
unset(SFML_SYSTEM)
unset(THRIFT)
unset( SFGUI)
unset( ALL_LIBS)
find_library(SFML_GRAPHICS NAMES "sfml-graphics" PATHS /home/harius/prog/junk/lib NO_DEFAULT_PATH)
find_library(SFML_WINDOW NAMES "sfml-window" PATHS /home/harius/prog/junk/lib NO_DEFAULT_PATH)
find_library(SFML_SYSTEM NAMES "sfml-system" PATHS /home/harius/prog/junk/lib NO_DEFAULT_PATH)
find_library(THRIFT NAMES "thrift-0.9.0-dev" PATHS /home/harius/prog/junk/lib NO_DEFAULT_PATH)
find_library(SFGUI NAMES "sfgui" PATHS /home/harius/prog/junk/lib NO_DEFAULT_PATH)

message (${SFML_GRAPHICS})

add_executable (log log.cpp)
target_link_libraries (log logger)

add_executable (view view.cpp)
target_link_libraries(view clientview clientmodel clientmodelgameobjectfactory
                      clientviewgameobjectfactory clientviewbonus clientviewwall clientviewbullet 
                      clientviewplayer clientviewunit clientviewgameobject
                      clientmodelbonus clientmodelwall clientmodelbullet clientmodelplayer clientmodelunit clientmodelgameobject
                      commonbonus commonwall commonbullet commonplayer commonunit commongameobject
                      clientnetworkmodel clientservicehandler logger utils
                      ${SFML_GRAPHICS} ${SFML_WINDOW} ${SFML_SYSTEM} ${THRIFT} ${SFGUI} pthread addressfetch clientconfig simplemenu hud)

add_executable (servertest server.cpp)
target_link_libraries(servertest server servermodel servernetworkmodel servergamemodel servermodelbonus servermodelwall
                      servermodelplayer servermodelbullet servermodelunit servermodelgameobject commonbonus commonwall
                      commonbullet commonplayer commonunit commongameobject clientservicehandler logger utils
                      sfml-graphics sfml-window sfml-system pthread thrift Box2D)

install (TARGETS view DESTINATION bin)
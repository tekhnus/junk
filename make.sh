LIBRARY=$LIBRARY' '-lsfml-system
LIBRARY=$LIBRARY' '-lsfml-network
LIBRARY=$LIBRARY' '-lsigc-2.0

CXX_FLAGS=$CXX_FLAGS' '-Wall
CXX_FLAGS=$CXX_FLAGS' '-std=c++0x

CXX_COMPILE=g++

$CXX_COMPILE -c src/client/Client.cpp -o build/Client.o $CXX_FLAGS $INCLUDE_PATH $LIBRARY
$CXX_COMPILE -c src/server/Server.cpp -o build/Server.o $CXX_FLAGS $INCLUDE_PATH $LIBRARY
$CXX_COMPILE -c src/logger/Logger.cpp -o build/Logger.o $CXX_FLAGS $INCLUDE_PATH $LIBRARY
$CXX_COMPILE -o build/log src/test/log.cpp $CXX_FLAGS $INCLUDE_PATH $LIBRARY
$CXX_COMPILE -o build/client src/test/client.cpp build/Client.o build/Logger.o $CXX_FLAGS $INCLUDE_PATH $LIBRARY
$CXX_COMPILE -o build/server src/test/server.cpp build/Server.o build/Logger.o $CXX_FLAGS $INCLUDE_PATH $LIBRARY

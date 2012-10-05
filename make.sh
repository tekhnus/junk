LIBRARY=$LIBRARY' '-lsfml-system
LIBRARY=$LIBRARY' '-lsfml-network
LIBRARY=$LIBRARY' '-lsigc-2.0

CXX_FLAGS=$CXX_FLAGS' '-Wall
CXX_FLAGS=$CXX_FLAGS' '-std=c++11
CXX_FLAGS=$CXX_FLAGS' '-I.' '-I/usr/include/sigc++-2.0
CXX_FLAGS=$CXX_FLAGS' '-I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include
CXX_FLAGS=$CXX_FLAGS' '-I/opt/local/include/sigc++-2.0

CXX_COMPILE=clang++

mkdir -p build
mkdir -p bin
cd src

$CXX_COMPILE -c client/Client.cpp -o ../build/Client.o $CXX_FLAGS $INCLUDE_PATH
$CXX_COMPILE -c server/Server.cpp -o ../build/Server.o $CXX_FLAGS $INCLUDE_PATH
$CXX_COMPILE -c logger/Logger.cpp -o ../build/Logger.o $CXX_FLAGS $INCLUDE_PATH

$CXX_COMPILE -o ../bin/log test/log.cpp ../build/Logger.o $CXX_FLAGS $INCLUDE_PATH $LIBRARY
$CXX_COMPILE -o ../bin/client test/client.cpp ../build/Client.o ../build/Logger.o $CXX_FLAGS $INCLUDE_PATH $LIBRARY
$CXX_COMPILE -o ../bin/server test/server.cpp ../build/Server.o ../build/Logger.o $CXX_FLAGS $INCLUDE_PATH $LIBRARY

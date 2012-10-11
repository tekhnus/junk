LIBRARY=$LIBRARY' '-lsfml-system
LIBRARY=$LIBRARY' '-lsfml-network
LIBRARY=$LIBRARY' '-lsfml-graphics
LIBRARY=$LIBRARY' '-lsfml-window
LIBRARY=$LIBRARY' '-lsigc-2.0
LIBRARY=$LIBRARY' '-lGL
LIBRARY=$LIBRARY' '-lthrift

CXX_FLAGS=$CXX_FLAGS' '-Wall
DEFINE_FLAGS=-DHAVE_NETINET_IN_H
CXX_FLAGS=$CXX_FLAGS' '-std=c++0x
#CXX_FLAGS=$CXX_FLAGS' '-stdlib=libc++
CXX_FLAGS=$CXX_FLAGS' '-I.' '-I/usr/include/sigc++-2.0
CXX_FLAGS=$CXX_FLAGS' '-I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include
CXX_FLAGS=$CXX_FLAGS' '-I/opt/local/include/sigc++-2.0' '-I/opt/local/include
CXX_FLAGS=$CXX_FLAGS' '-I/usr/local/include/thrift
CXX_FLAGS=$CXX_FLAGS' '-I/usr/include/boost
#CXX_FLAGS=$CXX_FLAGS' '-L/usr/local/lib

CXX_COMPILE=g++

mkdir -p build
mkdir -p bin
cd src

$CXX_COMPILE -c client/Client.cpp -o ../build/Client.o $CXX_FLAGS $INCLUDE_PATH
$CXX_COMPILE -c client/model/ClientModel.cpp $DEFINE_FLAGS -o ../build/ClientModel.o $CXX_FLAGS $INCLUDE_PATH
$CXX_COMPILE -c server/Server.cpp -o ../build/Server.o $CXX_FLAGS $INCLUDE_PATH
$CXX_COMPILE -c logger/Logger.cpp -o ../build/Logger.o $CXX_FLAGS $INCLUDE_PATH
$CXX_COMPILE -c unit/Unit.cpp -o ../build/Unit.o $CXX_FLAGS $INCLUDE_PATH
$CXX_COMPILE -c view/View.cpp -o ../build/View.o $CXX_FLAGS $INCLUDE_PATH

$CXX_COMPILE -o ../bin/log test/log.cpp ../build/Logger.o $CXX_FLAGS $INCLUDE_PATH $LIBRARY
$CXX_COMPILE -o ../bin/client test/client.cpp ../build/Client.o ../build/Logger.o $CXX_FLAGS $INCLUDE_PATH $LIBRARY
$CXX_COMPILE -o ../bin/server test/server.cpp ../build/Server.o ../build/Logger.o $CXX_FLAGS $INCLUDE_PATH $LIBRARY
$CXX_COMPILE -o ../bin/unit test/unit.cpp ../build/Unit.o $CXX_FLAGS $INCLUDE_PATH $LIBRARY
$CXX_COMPILE -o ../bin/view test/view.cpp ../build/View.o ../build/Unit.o $CXX_FLAGS $INCLUDE_PATH $LIBRARY

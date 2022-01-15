### Build instructions

```sh
cd junk

# My last build command. You mileage will vary.
cmake -B build \
    -DBoost_INCLUDE_DIR=$HOME/local/stow/boost_1_78_0/include \
    -DSFGUI_ROOT=$HOME/local/stow/sgui-0.4 \
    -Dbox2d_DIR=$HOME/local/stow/box2d-2.4.1/lib/cmake/box2d \
    -DThrift_DIR=$HOME/local/stow/thrift-0.15.0/lib/cmake/thrift \
    -DLibevent_DIR=$HOME/local/stow/libevent-2.1.12/lib/cmake/libevent
# If needed, install the missing dependencies and/or fix other problems
# and/or edit the properties in CMakeCache.txt and rerun this command.

cmake --build build

# Those are convenience wrappers around the binaries
# which launch them with the correct environment.
cmake --built build --target run-server
cmake --build build --target run-client
```

#### Dependency building advice

- Install **flex** and **bison** with your package manager
- Download, build and install **Boost** 1.78.0
- Install **SFML** with the system's package manager
- Download, build and install **SFGUI** 0.4.0
- Patch the error in the SFGUI/Config.hpp: change SFGUI_MINOR_VERSION to 4 and SFGUI_REVISION_VERSION to 0
- Download, build and install **Box2d** 2.4.1
- Download, build *with CMake* and install **libevent** (latest)
- Download, build *with CMake* and install **thrift** 0.15.0

Thrift building instruction: https://github.com/apache/thrift/blob/master/build/cmake/README.md
Approximate command:
```
cmake -B build \
    -DCMAKE_INSTALL_PREFIX=$HOME/local/stow/thrift-0.15.0 \
    -DBoost_INCLUDE_DIR=$HOME/local/stow/boost_1_78_0/include \
    -DWITH_PYTHON=OFF -DWITH_NODEJS=OFF -DWITH_JAVASCRIPT=OFF \
    -DWITH_LIBEVENT=ON \
    -DLIBEVENT_ROOT=$HOME/local/stow/libevent-2.1.12
```

Note:
If you decide to use a custom `CMAKE_INSTALL_PREFIX` for **SFML** on Mac, you also probably want
to alter `SFML_DEPENDENCIES_INSTALL_PREFIX` (unless you want to install the dependent frameworks globally).
Unfortunately, is such case you are forced to set `SFML_DEPENDENCIES_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}/Frameworks`.
Otherwise you will get a linking error at runtime.
TODO: Report this as a bug to SFML developers.

### Known issues

#### Collisions stopped working

Currently, nothing collides with anything. ¯\_(ツ)_/¯

#### Keyboard access problem

Currenly, keyboard state checking (via isKeyPressed(...)) is used.
For it to work on Mac, keyboard access should be granted in Preferences.
Note that if you launch the client from the Terminal,
the access should be granted to the Terminal, not to the app itself.

We should probably migrate to event polling.
This method won't require any explicit privelege granting.

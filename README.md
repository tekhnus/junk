### Build instructions

```sh
cd junk

# My last build command. You mileage will vary.
$ cmake -B build \
    -DBoost_ROOT=$HOME/local/stow/boost_1_78_0 \
    -DSFGUI_ROOT=$HOME/local/stow/sfgui-0.4.0 \
    -Dbox2d_ROOT=$HOME/local/stow/box2d-2.4.1 \
    -DThrift_ROOT=$HOME/local/stow/thrift-0.15.0 \
    -DLibevent_ROOT=$HOME/local/stow/libevent-2.1.12 \
    -DCMAKE_BUILD_TYPE=Debug
# If needed, install the missing dependencies and/or fix other problems
# and/or edit the properties in CMakeCache.txt and rerun this command.

$ cmake --build build

# Those are convenience wrappers around the binaries
# which launch them with the correct environment.
$ cmake --build build --target run-server
$ cmake --build build --target run-client
```

#### Dependency building advice

- Install **flex** and **bison** with your package manager
- Download **Boost** 1.78.0, build (all libraries) and install
- Install **SFML** with the system's package manager
- *Clone* the latest **SFGUI**, build and install
- Download **Box2d** 2.4.1, build and install
- Download the latest **libevent**, build *with CMake* and install
- Download **thrift** 0.15.0, build *with CMake* and install

Thrift building instruction: https://github.com/apache/thrift/blob/master/build/cmake/README.md
Approximate command:
```
$ cmake -B mybuild \
    -DCMAKE_FIND_PACKAGE_PREFER_CONFIG=TRUE \
    -DBoost_ROOT=$HOME/local/stow/boost_1_78_0 \
    -DLibevent_ROOT=$HOME/local/stow/libevent-2.1.12 \
    -DWITH_PYTHON=OFF -DWITH_NODEJS=OFF -DWITH_JAVASCRIPT=OFF \
    -DWITH_LIBEVENT=ON \
    -DBUILD_TESTING=OFF \
    -DCMAKE_INSTALL_PREFIX=$HOME/local/stow/thrift-0.15.0
$ cmake --build mybuild
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

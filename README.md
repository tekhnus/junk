### Build instructions

```sh
cd junk
mkdir build
cd build

cmake ..
# If needed, install the missing dependencies and/or fix other problems
# and/or edit the properties in CMakeCache.txt and rerun this command.

make

# Those are conveniency wrappers around the binaries
# which launch them with the correct environment.
make run-server
make run-client
```

#### Dependency building advices

- **thrift** should be built by CMake using the following instruction: https://github.com/apache/thrift/blob/master/build/cmake/README.md
  Building by ./configure shouldn't be used, as it won't generate the lib/cmake files.
- **libevent** (a dependency of **thfift**) also should be built using cmake
- This exact commit of **box2d** should be used: **8815e09**.
  It is not included in a stable release yet.
- If you decide to use a custom `CMAKE_INSTALL_PREFIX` for **SFML** on Mac, you also probably want
  to alter `SFML_DEPENDENCIES_INSTALL_PREFIX` (unless you want to install the dependent frameworks globally).
  Unfortunately, is such case you are forced to set `SFML_DEPENDENCIES_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}/Frameworks`.
  Otherwise you will get a linking error at runtime.
  TODO: Report this as a bug to SFML developers.

### Known issues

#### Keyboard access problem

Currenly, keyboard state checking (via isKeyPressed(...)) is used.
For it to work on Mac, keyboard access should be granted in Preferences.
Note that if you launch the client from the Terminal,
the access should be granted to the Terminal, not to the app itself.

We should probably migrate to event polling.
This method won't require any explicit privelege granting.

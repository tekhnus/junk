### Build instructions

- **thrift** should be built by CMake using the following instruction: https://github.com/apache/thrift/blob/master/build/cmake/README.md
  Building by ./configure shouldn't be used, as it won't generate the lib/cmake files.
- **libevent** (a dependency of **thfift**) also should be built using cmake
- This exact commit of **box2d** should be used: **8815e09**.
  It is not included in a stable release yet.

### Keyboard access issue

Currenly, keyboard state checking (via isKeyPressed(...)) is used.
For it to work on Mac, keyboard access should be granted in Preferences.
Note that if you launch the client from the Terminal,
the access should be granted to the Terminal, not to the app itself.

We should probably migrate to event polling.
This method won't require any explicit privelege granting.

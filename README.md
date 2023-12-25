### Build instructions
```sh
nix build

# Run:
./result/bin/server
./result/bin/client
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

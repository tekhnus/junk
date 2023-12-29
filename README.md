### Instructions

```sh
# Build:
nix develop
./scripts/build

# Run:
./build/server
./build/client
```

### Known issues

#### Build with optimizations crashes

I suspect that infinite for-loop in main() might be the cause.

#### Keyboard access problem

Currenly, keyboard state checking (via isKeyPressed(...)) is used.
For it to work on Mac, keyboard access should be granted in Preferences.
Note that if you launch the client from the Terminal,
the access should be granted to the Terminal, not to the app itself.

We should probably migrate to event polling.
This method won't require any explicit privelege granting.

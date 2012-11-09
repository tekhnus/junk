#!/usr/local/bin/thrift --gen cpp

namespace cpp junk

include "Shared.thrift"

typedef Shared.Vector2f Vector2f

struct GameObjectPatch {
  1: i32 objectID
}

struct UnitPatch {
  1: GameObjectPatch gameObjectPatch,
  2: Vector2f position,
  3: Vector2f direction
}

struct PlayerPatch {
  1: UnitPatch unitPatch
}

struct Patch {
  // Possible patches
  1: optional GameObjectPatch gameObjectPatch,
  2: optional UnitPatch unitPatch,
  3: optional PlayerPatch playerPatch
}

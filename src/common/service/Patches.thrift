#!/usr/local/bin/thrift --gen cpp

namespace cpp junk

include "Shared.thrift"

typedef Shared.Vector2f Vector2f

struct DestroyInfo {
  1: bool isDestructing,
  2: i32 destroyCountdown;
}

struct GameObjectPatch {
  1: i32 id
  2: DestroyInfo destroyInfo
}

struct UnitPatch {
  1: GameObjectPatch gameObjectPatch,
  2: Vector2f position,
  3: Vector2f direction
}

struct PlayerPatch {
  1: UnitPatch unitPatch
  2: i32 health
  3: i32 maxHealth
}

struct BulletPatch {
  1: UnitPatch unitPatch
}

enum GameObjectType {
  GAME_OBJECT = 1,
  UNIT = 2,
  PLAYER = 3,
  BULLET = 4
}

struct Patch {
  1: i32 id,
  2: GameObjectType gameObjectType,
  3: bool isCleanedUp,

  // Possible patches
  10: optional GameObjectPatch gameObjectPatch,
  11: optional UnitPatch unitPatch,
  12: optional PlayerPatch playerPatch,
  13: optional BulletPatch bulletPatch
}

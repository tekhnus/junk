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

struct BonusPatch {
  1: UnitPatch unitPatch,
  2: i32 bonusType
}

struct PlayerPatch {
  1: UnitPatch unitPatch
  2: i32 health
  3: i32 maxHealth
  4: string name
  5: i32 score
}

struct BulletPatch {
  1: UnitPatch unitPatch
  2: i32 type
  3: string owner
}

struct WallPatch {
  1: UnitPatch unitPatch,
  2: list<Vector2f> corners
}

enum GameObjectType {
  GAME_OBJECT = 1,
  UNIT = 2,
  PLAYER = 3,
  BULLET = 4,
  WALL = 5,
  BONUS = 6
}

struct Patch {
  1: i32 id,
  2: GameObjectType gameObjectType,
  3: bool isCleanedUp,

  // Possible patches
  10: optional GameObjectPatch gameObjectPatch,
  11: optional UnitPatch unitPatch,
  12: optional PlayerPatch playerPatch,
  13: optional BulletPatch bulletPatch,
  14: optional WallPatch wallPatch
  15: optional BonusPatch bonusPatch
}

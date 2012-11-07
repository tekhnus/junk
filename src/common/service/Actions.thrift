#!/usr/local/bin/thrift --gen cpp

namespace cpp junk

include "Shared.thrift"

typedef Shared.Vector2f Vector2f

struct MoveAction {
  1: Vector2f direction
}

struct RotateAction {
  1: Vector2f direction
}

struct FireAction {
  1: Vector2f direction
}

enum ActionType {
  MOVE = 1,
  ROTATE = 2,
  FIRE = 3
}

struct Action {
  1: ActionType actionType,
  2: i32 playerID,

  // Possible Actions
  10: optional MoveAction moveAction,
  11: optional RotateAction rotateAction,
  12: optional FireAction fireAction
}

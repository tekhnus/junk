#!/usr/local/bin/thrift --gen cpp

namespace cpp junk

include "Shared.thrift"

struct MoveAction {
  1: Shared.Vector2f direction
}

struct RotateAction {
  1: Shared.Vector2f direction
}

struct FireAction {
  1: bool on
}

struct ChangeSettingsAction {
  1: string name
}

enum ActionType {
  MOVE = 1,
  ROTATE = 2,
  FIRE = 3,
  CHANGE_SETTINGS = 4
}

struct Action {
  1: ActionType actionType,
  2: i32 playerId,

  // Possible Actions
  10: optional MoveAction moveAction,
  11: optional RotateAction rotateAction,
  12: optional FireAction fireAction,
  13: optional ChangeSettingsAction changeSettingsAction
}

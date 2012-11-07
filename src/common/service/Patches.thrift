#!/usr/local/bin/thrift --gen cpp

namespace cpp junk

include "Shared.thrift"

typedef Shared.Vector2f Vector2f

struct ModelUnitPatch {
  1: Vector2f position,
  2: Vector2f direction
}

enum ModelPatchType {
  MODEL_UNIT_PATCH = 1,
}

struct ModelPatch {
  1: ModelPatchType modelPatchType,
  2: i32 objectID,

  // Possible patches
  10: ModelUnitPatch modelUnitPatch
}

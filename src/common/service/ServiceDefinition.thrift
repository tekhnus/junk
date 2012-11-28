#!/usr/local/bin/thrift --gen cpp

namespace cpp junk

include "Shared.thrift"
include "Patches.thrift"
include "Actions.thrift"

struct GameChanges {
  1: list<Patches.Patch> patches,
}

struct SessionInfo {
  1: i32 id,
  2: binary uuid
}

struct ConnectInfo {
  1: string name
}

exception BadLogin {
}

service ClientService {
  SessionInfo connect(1: ConnectInfo connectInfo);

  GameChanges getChanges(1: SessionInfo sessionInfo) throws (1: BadLogin badLogin);

  void makeAction(1: SessionInfo sessionInfo, 2: Actions.Action action) throws (1: BadLogin badLogin);
}

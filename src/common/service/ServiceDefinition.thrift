#!/usr/local/bin/thrift --gen cpp

namespace cpp junk

struct Vector2f {
  1: double x,
  2: double y
}

struct PlayerInfo {
	1: i32 id,
	2: Vector2f position,
	3: Vector2f direction
}

struct GameChanges {
	list<PlayerInfo> players
}

struct GameState {
	1: list<PlayerInfo> players
}

service ClientService {
	i32 connect();
	void move(1: i32 id, 2: Vector2f direction);
	void rotate(1: i32 id, 2: Vector2f direction);
	void fire(1: i32 id, 2: Vector2f direction);
	#GameState getGameState(1: i32 id);
	GameChanges getChanges(1: i32 id);
}

#!/usr/local/bin/thrift --gen cpp

namespace cpp junk

struct Vector2f {
  1: double x,
  2: double y
}

service ClientService {
	void connect();
	void move(1: i32 id, 2: Vector2f direction);
	void rotate(1: i32 id, 2: Vector2f direction);
	void fire(1: i32 id, 2: Vector2f direction);
}

service ServerService {
	void connected(1: i32 id);
	void clientPositionUpdated(1: i32 id, 2: Vector2f position);
	void clientDirectionUpdated(1: i32 id, 2: Vector2f direction);
	void fireUpdated();
}


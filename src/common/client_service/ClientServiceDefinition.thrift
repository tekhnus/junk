#!/usr/local/bin/thrift --gen cpp

namespace cpp junk

struct Vector2f {
  1: double x,
  2: double y
}

service ClientService {
	void move(1: Vector2f direction);
	void changeDirection(1: Vector2f direction);
	void fire(1: Vector2f direction);
}

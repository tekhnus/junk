#!/usr/local/bin/thrift --gen cpp

namespace cpp junk

struct Vector2f {
  1: double x,
  2: double y
}

service ServerService {
	void clientPositionUpdated(1: i16 id, 2: Vector2f position);
	void clientDirectionUpdated(1: i16 id, 2: Vector2f direction);
	void fireUpdated();
}

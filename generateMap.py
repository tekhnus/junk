#!/usr/bin/python3

import json
from math import *
from random import Random

coord_range = 200
wall_count = int(coord_range * coord_range / 150)
approx_size = coord_range / 10

def gen():
  rng = Random(42)
  data = {}
  data["walls"] = []
  for wall_index in range(wall_count):
    size = rng.randint(1, approx_size)
    center_x = rng.randint(-coord_range, coord_range)
    center_y = rng.randint(-coord_range, coord_range)
    corners = []
    alpha = rng.random()
    for corner_index in range(3):
      angle = alpha + corner_index * 2 * pi / 3
      x = center_x + size * cos(angle)
      y = center_y + size * sin(angle)
      corner = {"x": x, "y": y}
      corners.append(corner)
    data["walls"].append(corners)
  return data

if __name__ == '__main__':
  data = gen()
  with open('resources/map.json', 'w') as fp:
    json.dump(data, fp)

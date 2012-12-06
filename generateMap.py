#!/usr/bin/python3

import json
from math import *
from random import randint, random

wall_count = 20
approx_size = 5
coord_range = 40

def gen():
  data = {}
  data["walls"] = []
  for wall_index in range(wall_count):
    size = randint(1, approx_size)
    center_x = randint(-coord_range, coord_range)
    center_y = randint(-coord_range, coord_range)
    corners = []
    alpha = random()
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
  with open('map.json', 'w') as fp:
    json.dump(data, fp)

#!/usr/bin/python3

import json
from random import randint

wall_count = 10
approx_size = 30
coord_range = 300

def gen():
  data = {}
  data["walls"] = []
  for wall_index in range(wall_count):
    size = randint(1, approx_size)
    center_x = randint(-coord_range, coord_range)
    center_y = randint(-coord_range, coord_range)
    corners = []
    for corner_index in range(3):
      x = randint(center_x - approx_size, center_x + approx_size)
      y = randint(center_y - approx_size, center_y + approx_size)
      corner = {"x": x, "y": y}
      corners.append(corner)
    data["walls"].append(corners)
  return data

if __name__ == '__main__':
  data = gen()
  with open('map.json', 'w') as fp:
    json.dump(data, fp)

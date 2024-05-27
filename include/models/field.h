#pragma once

#include <vector>

#include <models/ship.h>

#define GAME_SIZE 10
#define ONE_SHIP 4
#define TWO_SHIP 3
#define THREE_SHIP 2
#define FOUR_SHIP 1

enum FieldElement { NOT_CHECKED = 0, EMPTY_CHECKED = 1, EXPOLSION_CHECKED = 2 };

class Field {
public:
  FieldElement field[GAME_SIZE][GAME_SIZE] = {};
  std::vector<Ship> ships;

  static bool areInBounds(int pos);
  static Field generateRandom();
  bool validateShips();
};

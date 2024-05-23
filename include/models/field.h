#pragma once

#include <vector>

#include <models/ship.h>

#define GAME_SIZE 10
#define ONE_SHIP 4
#define THREE_SHIP 3
#define TWO_SHIP 2
#define FOUR_SHIP 1

enum FieldElement {
    NOT_CHECKED,
    EMPTY_CHECKED,
    EXPOLSION_CHECKED
};

class Field {
public:
    FieldElement field[GAME_SIZE][GAME_SIZE];
    std::vector<Ship> ships;

    static bool are_in_bounds(int pos) {
        return pos >= 0 && pos < GAME_SIZE;
    }

public:
    static Field generate_random();
    bool validate_ships();
};

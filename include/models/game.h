#pragma once

#include <models/field.h>
#include <game/server/server.h>

class Game {
public:
    bool game_over = false;
    bool youre_winner;
    bool youre_going;
    WinningReason reason = FAIR;
    Field own_field;
    Field enemy_field;
};

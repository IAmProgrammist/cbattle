#ifndef DUMP_H
#define DUMP_H

#include <vector>
#include <random>
#include <QDebug>

#define GAME_SIZE 10
#define ONE_SHIP 4
#define THREE_SHIP 3
#define TWO_SHIP 2
#define FOUR_SHIP 1

class Ship {
public:
    bool is_horizontal = true;
    int length = 1;
    int x = 0;
    int y = 0;

    Ship(bool is_horizontal,
         int length,
         int x,
         int y) {
        this->is_horizontal = is_horizontal;
        this->length = length;
        this->x = x;
        this->y = y;
    };
};

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

class Game {
    Field own_field;
    Field enemy_field;
};

class GameServerAdapter {
public:
    virtual void on_update() = 0;
    virtual void on_step(int x, int y) = 0;
    virtual void on_handshake(Field field, std::vector<Ship> ships) = 0;
};

class GameServer {
    bool going_one = true;
    bool player_one_handshake = false;
    bool player_two_handshake = false;
    GameServerAdapter* player_one;
    GameServerAdapter* player_two;

    Field player_one_field;
    Field player_two_field;
};

class GameClient {
public:
    virtual void on_update(Game g) = 0;
    virtual void on_step(int x, int y) = 0;
};

class LocalGameClient : GameClient {
    GameServerAdapter* conn;

    void on_update(Game g) {

    }

    void on_step(int x, int y) {
        conn->on_step(x, y);
    }
};

class BotGameClient : LocalGameClient {
    // Implement bot logic here later
};

#endif // DUMP_H

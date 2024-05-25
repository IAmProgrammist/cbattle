#pragma once

#include <game/client/client.h>
#include <models/field.h>
#include <stack>

enum Direction {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    UNKNOWN
};

class Suspicion {
public:
    int x = 0;
    int y = 0;
    Direction where = UNKNOWN;

    Suspicion();
    Suspicion(int x, int y, Direction where);
};

class BotGameClient : public GameClient {
    Game game;
    bool prev_step_mine = false;
    int prev_x = 0, prev_y = 0;
    Suspicion prev_suspicion = Suspicion();
    std::stack<Suspicion> suspicions;
public:
    BotGameClient();
    virtual ~BotGameClient();
    void on_update(Game g);
    void on_error(ErrorCode error);
    void init();
};

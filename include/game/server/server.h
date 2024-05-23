#pragma once

#include <models/field.h>

class ServerConnection;

class GameServer {
public:
    GameServer();

    bool going_one = true;
    ServerConnection* player_one;
    ServerConnection* player_two;

    Field player_one_field;
    Field player_two_field;
};

#ifndef GAMESERVER_H
#define GAMESERVER_H

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

#include <game/server/connection.h>

#endif // GAMESERVER_H

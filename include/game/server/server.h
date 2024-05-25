#pragma once

#include <mutex>

#include <models/field.h>

class ServerConnection;

class GameServer {
public:
    GameServer();

    std::mutex game_state_write;
    bool going_one = true;
    ServerConnection* player_one;
    ServerConnection* player_two;
    bool player_one_validated = false;
    bool player_two_validated = false;

    Field player_one_field;
    Field player_two_field;

    void on_handshake(ServerConnection* player, std::vector<Ship> ships);
    void on_step(ServerConnection* player, int x, int y);
    void send_update();
protected:
    static bool is_covered(Field& field, Ship& ship);
    static void cover_ship(Field& field, Ship& ship);
};

#pragma once

#include <mutex>

#include <models/field.h>

class ServerConnection;

enum ErrorCode {
    BAD_HANDSHAKE = 0,
    BAD_STEP = 1,
    NO_HANDSHAKE = 2,
    ALREADY_HANDSHAKE = 3
};

enum WinningReason {
    FAIR = 0,
    SURRENDER = 1
};

class GameServer {
public:
    GameServer();
    ~GameServer();

    std::mutex game_state_write;
    bool going_one = true;
    bool game_over = false;
    bool player_one_won = false;
    WinningReason winning_reason = FAIR;
    ServerConnection* player_one;
    ServerConnection* player_two;
    bool player_one_validated = false;
    bool player_two_validated = false;

    Field player_one_field;
    Field player_two_field;

    void on_handshake(ServerConnection* player, std::vector<Ship> ships);
    void on_step(ServerConnection* player, int x, int y);
    void on_surrender(ServerConnection* player);
    void check_game_over();
    void send_update();
protected:
    static bool is_covered(Field& field, Ship& ship);
    static void cover_ship(Field& field, Ship& ship);
};

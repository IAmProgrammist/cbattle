#pragma once

#include <models/game.h>

class GameServer;

class ServerConnection {
public:
    GameServer* game;
    ServerConnection(GameServer* game) : game(game) {};
    // This one is supposed to be called from server
    virtual void send_update(Game g) = 0;
    // This one is supposed to be called from client
    virtual void on_step(int x, int y) = 0;
    // As well as this
    virtual void on_handshake(std::vector<Ship> ships) = 0;
};

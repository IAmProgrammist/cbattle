#pragma once

#include <models/game.h>

class ClientConnection;

class GameClient {
public:
    ClientConnection *conn;
    // This method should be overriden on use
    virtual void on_update(Game g) = 0;
    void on_step(int x, int y);
    void on_handshake(Field field, std::vector<Ship> ships);
};

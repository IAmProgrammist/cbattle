#pragma once

#include <models/game.h>
#include <game/server/server.h>

class ClientConnection;

class GameClient {
public:
    ClientConnection *conn;
    // This method should be overriden on use
    virtual void on_update(Game g) = 0;
    virtual void on_error(ErrorCode error) = 0;
    virtual void init() = 0;
    virtual void on_step(int x, int y);
    virtual void on_handshake(std::vector<Ship> ships);
    virtual void on_surrender();
};

#pragma once

#include <thread>

#include <game/server/connection.h>
#include <game/client/connection.h>
#include <game/server/localconnection.h>
#include <game/client/connection.h>
#include <game/server/server.h>

class LocalServerConnection : public ServerConnection {
public:
    ClientConnection* conn;

    LocalServerConnection(GameServer* game) : ServerConnection(game) {}
    virtual ~LocalServerConnection() {}

    void send_update(Game g) {
        this->conn->on_update(g);
    }

    void send_error(ErrorCode error) {
        this->conn->on_error(error);
    }

    void on_step(int x, int y) {
        this->game->on_step(this, x, y);
    }

    void on_handshake(std::vector<Ship> ships) {
        this->game->on_handshake(this, ships);
    }

    void on_surrender() {
        this->game->on_surrender(this);
    }
};

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

    void send_update(Game g) {
        //std::thread thread([g, this] () {
            this->conn->on_update(g);
        //});

        //thread.detach();
    }

    void on_step(int x, int y) {
        //std::thread thread([x, y, this] () {
            this->game->on_step(this, x, y);
        //});

        //thread.detach();
    }

    void on_handshake(std::vector<Ship> ships) {
        //std::thread thread([ships, this] () {
            this->game->on_handshake(this, ships);
        //});

        //thread.detach();
    }
};

#pragma once

#include <models/field.h>
#include <models/game.h>

#include <game/client/connectionstrategy.h>
#include <game/server/server.h>

class ClientConnection {
public:
    ClientConnectionStrategy* strategy;
    ClientConnection(ClientConnectionStrategy* strategy);

    ~ClientConnection();

    void send_handshake(std::vector<Ship> ships);

    void send_step(int x, int y);

    void on_update(Game g);

    void on_error(ErrorCode error);

    void on_surrender();
};

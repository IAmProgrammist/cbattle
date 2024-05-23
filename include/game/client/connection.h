#pragma once

#include <models/field.h>
#include <models/game.h>

#include <game/client/connectionstrategy.h>

class ClientConnection {
public:
    ClientConnectionStrategy* strategy;
    ClientConnection(ClientConnectionStrategy* strategy) : strategy(strategy) {}
    void send_handshake(Field field, std::vector<Ship> ships) {
        return strategy->send_handshake(field, ships);
    }

    void send_step(int x, int y) {
        return strategy->send_step(x, y);
    }

    void on_update(Game g) {
        return strategy->on_update(g);
    }

};

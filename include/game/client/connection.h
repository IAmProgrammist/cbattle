#pragma once

#include <game/client/connectionstrategy.h>
#include <game/server/server.h>
#include <models/field.h>
#include <models/game.h>

class ClientConnection {
public:
    ClientConnectionStrategy* strategy;

    ClientConnection(ClientConnectionStrategy* strategy);
    ~ClientConnection();

    void sendHandshake(std::vector<Ship> ships);
    void sendStep(int x, int y);
    void onUpdate(Game g);
    void onError(ErrorCode error);
    void onSurrender();
};

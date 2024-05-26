#pragma once

#include <models/field.h>
#include <models/game.h>
#include <game/server/server.h>

class GameClient;

class ClientConnectionStrategy {
public:
    GameClient* client;

    ClientConnectionStrategy(GameClient* client);
    virtual ~ClientConnectionStrategy();

    virtual void sendHandshake(std::vector<Ship> ships) = 0;
    virtual void sendStep(int x, int y) = 0;
    virtual void onUpdate(Game g) = 0;
    virtual void onError(ErrorCode error) = 0;
    virtual void onSurrender() = 0;
};

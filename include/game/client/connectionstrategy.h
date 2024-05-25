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

    // This one is called from client, then it is transmitted to server
    virtual void send_handshake(std::vector<Ship> ships) = 0;
    // This one is called from client, then it is transmitted to server
    virtual void send_step(int x, int y) = 0;
    // This one is called from server, then it is transmitted to client
    virtual void on_update(Game g) = 0;
    virtual void on_error(ErrorCode error) = 0;
    virtual void on_surrender() = 0;
};

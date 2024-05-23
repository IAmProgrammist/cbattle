#ifndef CONNECTIONSTRATEGY_H
#define CONNECTIONSTRATEGY_H

#include <models/field.h>
#include <models/game.h>

class GameClient;

class ClientConnectionStrategy {
public:
    ClientConnectionStrategy(GameClient* client);

    GameClient* client;
    // This one is called from client, then it is transmitted to server
    virtual void send_handshake(Field field, std::vector<Ship> ships) = 0;
    // This one is called from client, then it is transmitted to server
    virtual void send_step(int x, int y) = 0;
    // This one is called from server, then it is transmitted to client
    virtual void on_update(Game g) = 0;
};

#include <game/client/client.h>

#endif // CONNECTIONSTRATEGY_H

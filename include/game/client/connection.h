#ifndef CONNECTION_H
#define CONNECTION_H

#include <models/field.h>
#include <models/game.h>

class ClientConnectionStrategy;

class ClientConnection {
public:
    ClientConnectionStrategy* strategy;
    ClientConnection(ClientConnectionStrategy* strategy);
    void send_handshake(Field field, std::vector<Ship> ships);
    void send_step(int x, int y);
    void on_update(Game g);
};

#include <game/client/connectionstrategy.h>

#endif // CONNECTION_H

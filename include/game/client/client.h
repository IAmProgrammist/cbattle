#ifndef CLIENT_H
#define CLIENT_H

#include <models/game.h>

class ClientConnection;

class GameClient {
public:
    ClientConnection *conn;
    // This method should be overriden on use
    virtual void on_update(Game g) = 0;
    void on_step(int x, int y);
    void on_handshake(Field field, std::vector<Ship> ships);
};

#include <game/client/connection.h>

#endif // CLIENT_H

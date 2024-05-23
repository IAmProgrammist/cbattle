#ifndef LOCALCONNECTIONSTRATEGY_H
#define LOCALCONNECTIONSTRATEGY_H

#include <models/field.h>
#include <models/game.h>

#include <game/client/connectionstrategy.h>

class ServerConnection;

class LocalClientConnectionStrategy : public ClientConnectionStrategy {
public:
    ServerConnection* conn;

    LocalClientConnectionStrategy(GameClient* client, ServerConnection* conn);
    void send_handshake(Field field, std::vector<Ship> ships);
    // This one is called from client, then it is transmitted to server
    void send_step(int x, int y);
    // This one is called from server, then it is transmitted to client
    void on_update(Game g);
};

#include <game/server/connection.h>

#endif // LOCALCONNECTIONSTRATEGY_H

#pragma once

#include <models/field.h>
#include <models/game.h>
#include <mutex>

#include <game/client/connectionstrategy.h>

class ServerConnection;

class LocalClientConnectionStrategy : public ClientConnectionStrategy {
public:
    ServerConnection* conn;

    LocalClientConnectionStrategy(GameClient* client, ServerConnection* conn);
    ~LocalClientConnectionStrategy();
    void send_handshake(std::vector<Ship> ships);
    // This one is called from client, then it is transmitted to server
    void send_step(int x, int y);
    // This one is called from server, then it is transmitted to client
    void on_update(Game g);
    void on_error(ErrorCode error);
    void on_surrender();
};

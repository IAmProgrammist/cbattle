#pragma once

#include <game/client/connection.h>
#include <game/client/connection.h>
#include <game/server/connection.h>
#include <game/server/localconnection.h>
#include <game/server/server.h>

class LocalServerConnection : public ServerConnection {
public:
    ClientConnection* conn;

    LocalServerConnection(GameServer* game);
    virtual ~LocalServerConnection();

    void sendUpdate(Game g);
    void sendError(ErrorCode error);
    void onStep(int x, int y);
    void onHandshake(std::vector<Ship> ships);
    void onSurrender();
};

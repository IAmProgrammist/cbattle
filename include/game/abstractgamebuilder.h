#pragma once

#include <QTcpSocket>

#include <game/client/client.h>
#include <game/server/localconnection.h>

class AbstractGameBuilder {
protected:
    GameServer *server = nullptr;
    GameClient *playing_client = nullptr;
    GameClient *vs_client = nullptr;
    bool playing_setup = false;
    bool vs_setup = false;
public:
    AbstractGameBuilder();
    virtual ~AbstractGameBuilder();
    virtual AbstractGameBuilder* playing(GameClient *client) = 0;
    virtual AbstractGameBuilder* playing(QTcpSocket *socket) = 0;
    virtual AbstractGameBuilder* vs(GameClient *client) = 0;
    virtual AbstractGameBuilder* vs(QTcpSocket *socket) = 0;
    virtual GameServer* begin() = 0;
};

#pragma once

#include <QObject>
#include <QTcpSocket>

#include <game/server/connection.h>
#include <game/server/server.h>

class TCPServerConnection : public QObject, public ServerConnection  {
    Q_OBJECT
public:
    QTcpSocket* conn;
    QByteArray temp;

    TCPServerConnection(GameServer* game, QTcpSocket* conn);
    virtual ~TCPServerConnection();

    void onReadyRead();
    void sendUpdate(Game g);
    void sendError(ErrorCode error);
    void onStep(int x, int y);
    void onHandshake(std::vector<Ship> ships);
    void onSurrender();
};

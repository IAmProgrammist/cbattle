#pragma once

#include <models/field.h>
#include <models/game.h>
#include <QTcpSocket>

#include <game/client/connectionstrategy.h>

class TCPClientConnectionStrategy : public QObject, public ClientConnectionStrategy {
    Q_OBJECT
public:
    QTcpSocket* conn;
    QByteArray temp;

    TCPClientConnectionStrategy(GameClient* client, QTcpSocket* conn, QObject *parent);
    ~TCPClientConnectionStrategy();
    void send_handshake(std::vector<Ship> ships);
    // This one is called from client, then it is transmitted to server
    void send_step(int x, int y);
    // This one is called from server, then it is transmitted to client
    void on_update(Game g);
    void on_error(ErrorCode error);
    void on_surrender();
protected:
    void onReadyRead();
};

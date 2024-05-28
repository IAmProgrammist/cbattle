#pragma once

#include <QObject>
#include <QTcpSocket>

#include <game/server/connection.h>
#include <game/server/server.h>

class TCPServerConnection : public QObject, public ServerConnection {
  Q_OBJECT

  QTcpSocket *conn;
  QByteArray temp;
  void onReadyRead();
public:
  TCPServerConnection(GameServer *game, QTcpSocket *conn);
  virtual ~TCPServerConnection();

  void sendUpdate(Game g);
  void sendError(ErrorCode error);
  void onStep(int x, int y);
  void onHandshake(std::vector<Ship> ships);
  void onSurrender();
};

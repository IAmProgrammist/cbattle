#pragma once

#include <QTcpSocket>

#include <game/client/connectionstrategy.h>
#include <models/field.h>
#include <models/game.h>

class TCPClientConnectionStrategy : public QObject,
                                    public ClientConnectionStrategy {
  Q_OBJECT
public:
  QTcpSocket *conn;
  QByteArray temp;

  TCPClientConnectionStrategy(GameClient *client, QTcpSocket *conn,
                              QObject *parent);
  ~TCPClientConnectionStrategy();
  void sendHandshake(std::vector<Ship> ships);
  void sendStep(int x, int y);
  void onUpdate(Game g);
  void onError(ErrorCode error);
  void onSurrender();

protected:
  void onReadyRead();
};

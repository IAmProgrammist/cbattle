#pragma once

#include <QTcpServer>

#include <game/client/client.h>
#include <game/server/localconnection.h>
#include <game/server/server.h>
#include <game/abstractgamebuilder.h>

class GameBuilder : public AbstractGameBuilder {
private:
  LocalServerConnection *establishLocalConnection(GameClient *client);

public:
  GameBuilder();
  ~GameBuilder();
  AbstractGameBuilder* playing(GameClient *client);
  AbstractGameBuilder* playing(QTcpSocket *socket);
  AbstractGameBuilder* vs(GameClient *client);
  AbstractGameBuilder* vs(QTcpSocket *socket);
  GameServer* begin();
};

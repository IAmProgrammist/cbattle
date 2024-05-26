#pragma once

#include <QTcpServer>

#include <game/client/client.h>
#include <game/server/localconnection.h>
#include <game/server/server.h>

class GameBuilder {
private:
  LocalServerConnection *establishLocalConnection(GameClient *client);

public:
  GameServer *server = nullptr;
  GameClient *playing_client = nullptr;
  GameClient *vs_client = nullptr;
  GameBuilder();
  GameBuilder &playing(GameClient *client);
  GameBuilder &playing(QTcpSocket *socket);
  GameBuilder &vs(GameClient *client);
  GameBuilder &vs(QTcpSocket *socket);
  void begin();
  void destroy();
};

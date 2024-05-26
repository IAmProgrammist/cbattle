#pragma once

#include <models/field.h>
#include <models/game.h>

#include <game/client/connectionstrategy.h>

class ServerConnection;

class LocalClientConnectionStrategy : public ClientConnectionStrategy {
public:
  ServerConnection *conn;

  LocalClientConnectionStrategy(GameClient *client, ServerConnection *conn);
  ~LocalClientConnectionStrategy();
  void sendHandshake(std::vector<Ship> ships);
  void sendStep(int x, int y);
  void onUpdate(Game g);
  void onError(ErrorCode error);
  void onSurrender();
};

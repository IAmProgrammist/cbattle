#pragma once

#include <models/field.h>
#include <models/game.h>

#include <game/client/connectionstrategy.h>

class ServerConnection;

class LocalClientConnectionStrategy : public ClientConnectionStrategy {
  ServerConnection *conn;
public:
  LocalClientConnectionStrategy(GameClient *client, ServerConnection *conn);
  ~LocalClientConnectionStrategy();
  void sendHandshake(std::vector<Ship> ships);
  void sendStep(int x, int y);
  void onUpdate(Game g);
  void onError(ErrorCode error);
  void onSurrender();
};

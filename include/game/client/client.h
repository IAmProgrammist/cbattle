#pragma once

#include <game/client/connection.h>
#include <game/server/server.h>
#include <models/game.h>

class GameClient {
public:
  ClientConnection *conn;
  virtual void onUpdate(Game g) = 0;
  virtual void onError(ErrorCode error) = 0;
  virtual void init() = 0;
  virtual void onStep(int x, int y);
  virtual void onHandshake(std::vector<Ship> ships);
  virtual void onSurrender();
};

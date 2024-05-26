#pragma once

#include <game/server/server.h>
#include <models/game.h>

class ServerConnection {
public:
  GameServer *game;
  ServerConnection(GameServer *game);
  virtual ~ServerConnection();

  virtual void sendUpdate(Game g) = 0;
  virtual void sendError(ErrorCode error) = 0;
  virtual void onStep(int x, int y) = 0;
  virtual void onHandshake(std::vector<Ship> ships) = 0;
  virtual void onSurrender() = 0;
};

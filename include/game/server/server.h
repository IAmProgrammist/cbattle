#pragma once

#include <models/field.h>

class ServerConnection;

enum ErrorCode {
  BAD_HANDSHAKE = 0,
  BAD_STEP = 1,
  NO_HANDSHAKE = 2,
  ALREADY_HANDSHAKE = 3
};

enum WinningReason { FAIR = 0, SURRENDER = 1 };

class GameServer {
  bool going_one = true;
  bool game_over = false;
  bool player_one_won = false;
  WinningReason winning_reason = FAIR;
  Field player_one_field;
  bool player_one_validated = false;
  Field player_two_field;
  bool player_two_validated = false;
  static bool isCovered(Field &field, Ship &ship);
  static void coverShip(Field &field, Ship &ship);
  void checkGameOver();

public:
  GameServer();
  ~GameServer();

  ServerConnection *player_one;
  ServerConnection *player_two;
  
  void onHandshake(ServerConnection *player, std::vector<Ship> ships);
  void onStep(ServerConnection *player, int x, int y);
  void onSurrender(ServerConnection *player);
  void sendUpdate();
};

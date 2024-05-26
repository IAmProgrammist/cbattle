#include <game/gamebuilder.h>

#include <QTcpSocket>
#include <game/client/connection.h>
#include <game/client/localconnectionstrategy.h>
#include <game/server/server.h>
#include <game/server/tcpconnection.h>.h>

LocalServerConnection *
GameBuilder::establishLocalConnection(GameClient *client) {
  auto server_conn = new LocalServerConnection(server);

  auto hostClientConnection = new ClientConnection(
      new LocalClientConnectionStrategy(client, server_conn));
  client->conn = hostClientConnection;
  server_conn->conn = hostClientConnection;

  return server_conn;
}

GameBuilder::GameBuilder() { this->server = new GameServer(); };

GameBuilder &GameBuilder::playing(GameClient *client) {
  server->player_one = establishLocalConnection(client);
  playing_client = client;

  return *this;
}

GameBuilder &GameBuilder::playing(QTcpSocket *socket) {
  server->player_one = new TCPServerConnection(this->server, socket);

  return *this;
}

GameBuilder &GameBuilder::vs(GameClient *client) {
  server->player_two = establishLocalConnection(client);
  vs_client = client;

  return *this;
}

GameBuilder &GameBuilder::vs(QTcpSocket *socket) {
  server->player_two = new TCPServerConnection(this->server, socket);

  return *this;
}

void GameBuilder::begin() {
  if (playing_client)
    playing_client->init();
  if (vs_client)
    vs_client->init();
}

void GameBuilder::destroy() {
  if (playing_client) {
    auto playing_conn = playing_client->conn;
    playing_client->conn = nullptr;
    delete playing_conn;
  }

  if (vs_client) {
    auto vs_conn = vs_client->conn;
    vs_client->conn = nullptr;
    delete vs_conn;
  }

  delete server;
}

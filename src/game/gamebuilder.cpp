#include <game/gamebuilder.h>

#include <QTcpSocket>
#include <game/client/connection.h>
#include <game/client/localconnectionstrategy.h>
#include <game/server/server.h>
#include <game/server/tcpconnection.h>

LocalServerConnection *
GameBuilder::establishLocalConnection(GameClient *client) {
  auto server_conn = new LocalServerConnection(server);

  auto host_client_connection = new ClientConnection(
      new LocalClientConnectionStrategy(client, server_conn));
  client->conn = host_client_connection;
  server_conn->conn = host_client_connection;

  return server_conn;
}

GameBuilder::GameBuilder() : AbstractGameBuilder() { this->server = new GameServer(); };

GameBuilder::~GameBuilder() {}

AbstractGameBuilder* GameBuilder::playing(GameClient *client) {
  server->player_one = establishLocalConnection(client);
  playing_client = client;
  playing_setup = true;

  return this;
}

AbstractGameBuilder* GameBuilder::playing(QTcpSocket *socket) {
  server->player_one = new TCPServerConnection(this->server, socket);
  playing_setup = true;

  return this;
}

AbstractGameBuilder* GameBuilder::vs(GameClient *client) {
  server->player_two = establishLocalConnection(client);
  vs_client = client;
  vs_setup = true;

  return this;
}

AbstractGameBuilder* GameBuilder::vs(QTcpSocket *socket) {
  server->player_two = new TCPServerConnection(this->server, socket);
  vs_setup = true;

  return this;
}

GameServer* GameBuilder::begin() {
  if (!playing_setup) throw std::runtime_error("Player is not set up, call playing... method in builder");
  if (!vs_setup) throw std::runtime_error("Player is not set up, call vs... method in builder");
  if (playing_client)
    playing_client->init();
  if (vs_client)
    vs_client->init();

  return this->server;
}

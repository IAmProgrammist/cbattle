#include <game/gamebuilder.h>

#include <game/client/localconnectionstrategy.h>
#include <game/client/connection.h>
#include <game/server/server.h>

LocalServerConnection* GameBuilder::establishLocalConnection(GameClient* client) {
    auto server_conn = new LocalServerConnection(server);

    auto hostClientConnection = new ClientConnection(new LocalClientConnectionStrategy(client, server_conn));
    client->conn = hostClientConnection;
    server_conn->conn = hostClientConnection;

    return server_conn;
}

GameBuilder::GameBuilder() {
    this->server = new GameServer();
};

GameBuilder& GameBuilder::playing(GameClient* client) {
    server->player_one = establishLocalConnection(client);
    playing_client = client;

    return *this;
}

GameBuilder& GameBuilder::playing(std::string ip, int port) {


    return *this;
}

GameBuilder& GameBuilder::vs(GameClient* client) {
    server->player_two = establishLocalConnection(client);
    vs_client = client;

    return *this;
}

GameBuilder& GameBuilder::vs(std::string ip, int port) {


    return *this;
}

void GameBuilder::begin() {
    playing_client->init();
    vs_client->init();
}

void GameBuilder::destroy() {
    auto playing_conn = playing_client->conn;
    playing_client->conn = nullptr;
    delete playing_conn;

    auto vs_conn = vs_client->conn;
    vs_client->conn = nullptr;
    delete vs_conn;

    delete server;
}

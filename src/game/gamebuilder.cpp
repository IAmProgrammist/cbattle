#include <game/gamebuilder.h>

#include <game/client/localconnectionstrategy.h>

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

void GameBuilder::playing(GameClient* client) {
    server->player_one = establishLocalConnection(client);
}

void GameBuilder::playing(std::string ip, int port) {

}

void GameBuilder::vs(GameClient* client) {
    server->player_two = establishLocalConnection(client);
}

void GameBuilder::vs(std::string ip, int port) {

}

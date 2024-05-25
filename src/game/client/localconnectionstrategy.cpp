#include <game/client/localconnectionstrategy.h>
#include <game/server/connection.h>
#include <game/client/client.h>

LocalClientConnectionStrategy::LocalClientConnectionStrategy(GameClient* client, ServerConnection* conn) : ClientConnectionStrategy(client), conn(conn) {}

LocalClientConnectionStrategy::~LocalClientConnectionStrategy() {}

void LocalClientConnectionStrategy::send_handshake(std::vector<Ship> ships) {
    conn->on_handshake(ships);
}

void LocalClientConnectionStrategy::send_step(int x, int y) {
    conn->on_step(x, y);
}

void LocalClientConnectionStrategy::on_update(Game g) {
    this->client->on_update(g);
}

void LocalClientConnectionStrategy::on_error(ErrorCode error) {
    this->client->on_error(error);
}

void LocalClientConnectionStrategy::on_surrender() {
    conn->on_surrender();
}

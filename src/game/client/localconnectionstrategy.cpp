#include <game/client/localconnectionstrategy.h>
#include <game/server/connection.h>
#include <game/client/client.h>

LocalClientConnectionStrategy::LocalClientConnectionStrategy(GameClient* client, ServerConnection* conn) : ClientConnectionStrategy(client), conn(conn) {}

void LocalClientConnectionStrategy::send_handshake(Field field, std::vector<Ship> ships) {
    conn->on_handshake(field, ships);
}

void LocalClientConnectionStrategy::send_step(int x, int y) {
    conn->on_step(x, y);
}

void LocalClientConnectionStrategy::on_update(Game g) {
    this->client->on_update(g);
}

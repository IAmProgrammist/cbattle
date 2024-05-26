#include <game/client/localconnectionstrategy.h>
#include <game/server/connection.h>
#include <game/client/client.h>

LocalClientConnectionStrategy::LocalClientConnectionStrategy(GameClient* client, ServerConnection* conn) : ClientConnectionStrategy(client), conn(conn) {}

LocalClientConnectionStrategy::~LocalClientConnectionStrategy() {}

void LocalClientConnectionStrategy::sendHandshake(std::vector<Ship> ships) {
    conn->onHandshake(ships);
}

void LocalClientConnectionStrategy::sendStep(int x, int y) {
    conn->onStep(x, y);
}

void LocalClientConnectionStrategy::onUpdate(Game g) {
    this->client->onUpdate(g);
}

void LocalClientConnectionStrategy::onError(ErrorCode error) {
    this->client->onError(error);
}

void LocalClientConnectionStrategy::onSurrender() {
    conn->onSurrender();
}

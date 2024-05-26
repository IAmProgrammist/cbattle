#include <game/client/client.h>
#include <game/client/connection.h>

void GameClient::onStep(int x, int y) {
    return conn->sendStep(x, y);
}

void GameClient::onHandshake(std::vector<Ship> ships) {
    return conn->sendHandshake(ships);
}

void GameClient::onSurrender() {
    return conn->onSurrender();
}

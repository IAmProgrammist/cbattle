#include <game/client/connection.h>

ClientConnection::ClientConnection(ClientConnectionStrategy* strategy) : strategy(strategy) {}

ClientConnection::~ClientConnection() {
    delete strategy;
}

void ClientConnection::sendHandshake(std::vector<Ship> ships) {
    return strategy->sendHandshake(ships);
}

void ClientConnection::sendStep(int x, int y) {
    return strategy->sendStep(x, y);
}

void ClientConnection::onUpdate(Game g) {
    return strategy->onUpdate(g);
}

void ClientConnection::onError(ErrorCode error) {
    return strategy->onError(error);
}

void ClientConnection::onSurrender() {
    return strategy->onSurrender();
}

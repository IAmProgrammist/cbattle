#include <game/client/connection.h>

ClientConnection::ClientConnection(ClientConnectionStrategy* strategy) : strategy(strategy) {}

ClientConnection::~ClientConnection() {
    delete strategy;
}

void ClientConnection::send_handshake(std::vector<Ship> ships) {
    return strategy->send_handshake(ships);
}

void ClientConnection::send_step(int x, int y) {
    return strategy->send_step(x, y);
}

void ClientConnection::on_update(Game g) {
    return strategy->on_update(g);
}

void ClientConnection::on_error(ErrorCode error) {
    return strategy->on_error(error);
}

void ClientConnection::on_surrender() {
    return strategy->on_surrender();
}

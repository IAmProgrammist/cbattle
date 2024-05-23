#include <game/client/connection.h>

ClientConnection::ClientConnection(ClientConnectionStrategy* strategy) : strategy(strategy) {}

void ClientConnection::send_handshake(Field field, std::vector<Ship> ships) {
    return strategy->send_handshake(field, ships);
}

void ClientConnection::send_step(int x, int y) {
    return strategy->send_step(x, y);
}

void ClientConnection::on_update(Game g) {
    return strategy->on_update(g);
}

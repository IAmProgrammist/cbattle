#include <game/client/client.h>
#include <game/client/connection.h>

void GameClient::on_step(int x, int y) {
    return conn->send_step(x, y);
}

void GameClient::on_handshake(std::vector<Ship> ships) {
    return conn->send_handshake(ships);
}

void GameClient::on_surrender() {
    return conn->on_surrender();
}

#include <game/client/client.h>

void GameClient::on_step(int x, int y) {
    return conn->send_step(x, y);
}

void GameClient::on_handshake(Field field, std::vector<Ship> ships) {
    return conn->send_handshake(field, ships);
}

#include <game/server/localconnection.h>
#include <game/client/connection.h>

LocalServerConnection::LocalServerConnection(GameServer* game) : ServerConnection(game) {}

void LocalServerConnection::send_update(Game g) {
    this->conn->on_update(g);
}

void LocalServerConnection::on_step(int x, int y) {
    // TODO: call step for server
}

void LocalServerConnection::on_handshake(Field field, std::vector<Ship> ships) {
    // TODO: call handshake for server
}

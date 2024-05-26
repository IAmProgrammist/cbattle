#include <game/server/localconnection.h>

LocalServerConnection::LocalServerConnection(GameServer* game) : ServerConnection(game) {}
LocalServerConnection::~LocalServerConnection() {}

void LocalServerConnection::sendUpdate(Game g) {
    this->conn->onUpdate(g);
}

void LocalServerConnection::sendError(ErrorCode error) {
    this->conn->onError(error);
}

void LocalServerConnection::onStep(int x, int y) {
    this->game->onStep(this, x, y);
}

void LocalServerConnection::onHandshake(std::vector<Ship> ships) {
    this->game->onHandshake(this, ships);
}

void LocalServerConnection::onSurrender() {
    this->game->onSurrender(this);
}

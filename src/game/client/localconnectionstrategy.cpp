#include <thread>

#include <game/client/localconnectionstrategy.h>
#include <game/server/connection.h>
#include <game/client/client.h>

LocalClientConnectionStrategy::LocalClientConnectionStrategy(GameClient* client, ServerConnection* conn) : ClientConnectionStrategy(client), conn(conn) {}

void LocalClientConnectionStrategy::send_handshake(std::vector<Ship> ships) {
    //std::thread thread([ships, this] () {
        conn->on_handshake(ships);
    //});

    //thread.detach();
}

void LocalClientConnectionStrategy::send_step(int x, int y) {
    //std::thread thread([x, y, this] () {
        conn->on_step(x, y);
    //});

    //thread.detach();
}

void LocalClientConnectionStrategy::on_update(Game g) {
    //std::thread thread([g, this] () {
    //    this->update_mutex.lock();
        this->client->on_update(g);
    //    this->update_mutex.unlock();
    //});

    //thread.detach();
}

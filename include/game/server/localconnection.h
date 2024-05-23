#ifndef LOCALCONNECTION_H
#define LOCALCONNECTION_H

#include <game/server/connection.h>
#include <game/client/connection.h>

class LocalServerConnection : public ServerConnection {
public:
    ClientConnection* conn;
    LocalServerConnection(GameServer* game);
    void send_update(Game g);
    void on_step(int x, int y);
    void on_handshake(Field field, std::vector<Ship> ships);
};

#endif // LOCALCONNECTION_H

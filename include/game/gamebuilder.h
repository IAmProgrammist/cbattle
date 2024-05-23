#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include <game/client/client.h>
#include <game/server/localconnection.h>
#include <game/server/server.h>
#include <string>

class GameBuilder {
private:
    LocalServerConnection* establishLocalConnection(GameClient* client);

public:
    GameServer* server;
    GameBuilder();
    void playing(GameClient* client);
    void playing(std::string ip, int port);
    void vs(GameClient* client);
    void vs(std::string ip, int port);
    void begin();
};

#endif // GAMEBUILDER_H

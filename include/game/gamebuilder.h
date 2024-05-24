#pragma once

#include <game/client/client.h>
#include <game/server/localconnection.h>
#include <game/server/server.h>
#include <string>

class GameBuilder {
private:
    LocalServerConnection* establishLocalConnection(GameClient* client);

public:
    GameServer* server;
    GameClient* playing_client;
    GameClient* vs_client;
    GameBuilder();
    GameBuilder& playing(GameClient* client);
    GameBuilder& playing(std::string ip, int port);
    GameBuilder& vs(GameClient* client);
    GameBuilder& vs(std::string ip, int port);
    void begin();
};

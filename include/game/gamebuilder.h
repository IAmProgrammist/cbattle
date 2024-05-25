#pragma once

#include <game/client/client.h>
#include <game/server/localconnection.h>
#include <game/server/server.h>
#include <string>

class GameBuilder {
private:
    LocalServerConnection* establishLocalConnection(GameClient* client);

public:
    GameServer* server = nullptr;
    GameClient* playing_client = nullptr;
    GameClient* vs_client = nullptr;
    GameBuilder();
    GameBuilder& playing(GameClient* client);
    GameBuilder& playing(std::string ip, int port);
    GameBuilder& vs(GameClient* client);
    GameBuilder& vs(std::string ip, int port);
    void begin();
    void destroy();
};

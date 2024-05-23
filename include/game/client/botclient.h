#ifndef BOTCLIENT_H
#define BOTCLIENT_H

#include <game/client/client.h>

class BotGameClient : public GameClient {
public:
    BotGameClient();

    void on_update(Game g);
};

#endif // BOTCLIENT_H

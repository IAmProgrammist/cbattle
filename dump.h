#ifndef DUMP_H
#define DUMP_H

#include <vector>
#include <random>
#include <QDebug>


#include <models/ship.h>
#include <models/field.h>



/*
class ServerConnection;

class GameServer {
    friend class GameServerBuilder;
    GameServer() = default;
    bool going_one = true;
    ServerConnection* player_one;
    ServerConnection* player_two;

    Field player_one_field;
    Field player_two_field;
};

class ServerConnection {
protected:
    GameServer* game;
    ServerConnection() {};
public:
    // This one is supposed to be called from server
    virtual void send_update() = 0;

    // This one is supposed to be called from client
    virtual void on_step(int x, int y) = 0;
    // As well as this
    virtual void on_handshake(Field field, std::vector<Ship> ships) = 0;
};

class GameServerBuilder;
class GameClient;

class ClientConnectionStrategy {
public:
    GameClient* client;
    // This one is called from client, then it is transmitted to server
    virtual void send_handshake(Field field, std::vector<Ship> ships) = 0;
    // This one is called from client, then it is transmitted to server
    virtual void send_step(int x, int y) = 0;
    // This one is called from server, then it is transmitted to client
    virtual void on_update(Game g) = 0;
};

class LocalClientConnectionStrategy : public ClientConnectionStrategy {
public:
    ServerConnection* conn;
    void send_handshake(Field field, std::vector<Ship> ships) {
        conn->on_handshake(field, ships);
    }
    // This one is called from client, then it is transmitted to server
    void send_step(int x, int y) {
        conn->on_step(x, y);
    }
    // This one is called from server, then it is transmitted to client
    void on_update(Game g) {
        this->client->on_update(g);
    }
};

class ClientConnection {
public:
    ClientConnectionStrategy* strategy;
    // This one is called from client, then it is transmitted to server
    void send_handshake(Field field, std::vector<Ship> ships) {
        return strategy->send_handshake(field, ships);
    }
    // This one is called from client, then it is transmitted to server
    virtual void send_step(int x, int y) {
        return strategy->send_step(x, y);
    }
    // This one is called from server, then it is transmitted to client
    virtual void on_update(Game g) {
        return strategy->on_update(g);
    }
};

class GameClient {
protected:
    ClientConnection *strategy;
public:

    // This method should be overriden on use
    virtual void on_update(Game g) = 0;

    void on_step(int x, int y) {
        return strategy->send_step(x, y);
    }

    void on_handshake(Field field, std::vector<Ship> ships) {
        return strategy->send_handshake(field, ships);
    }
};*/

#endif // DUMP_H

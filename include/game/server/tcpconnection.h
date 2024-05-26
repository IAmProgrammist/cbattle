#pragma once

#include <game/server/connection.h>
#include <game/client/connection.h>
#include <game/server/localconnection.h>
#include <game/client/connection.h>
#include <game/server/server.h>
#include <QObject>
#include <QTcpSocket>
#include <sstream>

class TCPServerConnection : public QObject, public ServerConnection  {
    Q_OBJECT
public:
    QTcpSocket* conn;
    QByteArray temp;

    TCPServerConnection(GameServer* game, QTcpSocket* conn) : QObject(nullptr), ServerConnection(game), conn(conn)  {
        this->conn = conn;
        connect(conn, &QTcpSocket::readyRead, this, &TCPServerConnection::onReadyRead);
        connect(conn, &QTcpSocket::disconnected, this, &TCPServerConnection::on_surrender);
    }

    virtual ~TCPServerConnection() {
        conn->flush();
        conn->close();
        delete conn;
    }

    void onReadyRead() {
        QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
        if (!clientSocket)
            return;

        QByteArray data = clientSocket->readAll();
        for (auto &b : data) {
            if (b != '\n') {
                temp.append(b);
                continue;
            }

            if (temp.toStdString().rfind("handshake: ", 0) == 0) {
                std::stringstream input(temp.toStdString().substr(11));
                int sh_amount;
                input >> sh_amount;
                std::vector<Ship> ships;
                for (int i = 0; i < sh_amount; i++) {
                    int dat;
                    input >> dat;
                    bool is_horizontal = dat == 1;
                    int length;
                    input >> length;
                    int x;
                    input >> x;
                    int y;
                    input >> y;
                    ships.push_back(Ship(is_horizontal, length, x, y));
                }

                on_handshake(ships);
            } else if (temp.toStdString().rfind("step: ", 0) == 0) {
                std::stringstream input(temp.toStdString().substr(6));
                int x, y;
                input >> x >> y;

                on_step(x, y);
            } else if (temp.toStdString().rfind("surrender: ", 0) == 0) {
                on_surrender();
            }

            temp.clear();
        }
    }

    void send_update(Game g) {
        std::stringstream output;
        output << "update: " << (g.game_over ? 1 : 0) << " " <<
            (g.youre_winner ? 1 : 0) << " " <<
            (g.youre_going ? 1 : 0) << " " << static_cast<int>(g.reason) << " ";

        for (int i = 0; i < GAME_SIZE; i++) {
            for (int j = 0; j < GAME_SIZE; j++) {
                output << static_cast<int>(g.own_field.field[i][j]) << " ";
            }
        }
        output << g.own_field.ships.size() << " ";
        for (auto & ship : g.own_field.ships) {
            output << (ship.is_horizontal ? 1 : 0) << " " << ship.length << " " << ship.x << " " << ship.y << " ";
        }

        for (int i = 0; i < GAME_SIZE; i++) {
            for (int j = 0; j < GAME_SIZE; j++) {
                output << static_cast<int>(g.enemy_field.field[i][j]) << " ";
            }
        }
        output << g.enemy_field.ships.size() << " ";
        for (auto & ship : g.enemy_field.ships) {
            output << (ship.is_horizontal ? 1 : 0) << " " << ship.length << " " << ship.x << " " << ship.y << " ";
        }

        output << "\n";

        conn->write(output.str().c_str());
        conn->flush();
    }

    void send_error(ErrorCode error) {
        std::stringstream output;
        output << "error: " << static_cast<int>(error) << "\n";

        conn->write(output.str().c_str());
        conn->flush();
    }

    void on_step(int x, int y) {
        this->game->on_step(this, x, y);
    }

    void on_handshake(std::vector<Ship> ships) {
        this->game->on_handshake(this, ships);
    }

    void on_surrender() {
        this->game->on_surrender(this);
    }
};

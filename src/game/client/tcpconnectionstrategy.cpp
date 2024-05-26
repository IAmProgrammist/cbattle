#include <game/client/client.h>
#include <game/client/tcpconnectionstrategy.h>
#include <game/server/connection.h>

#include <sstream>

TCPClientConnectionStrategy::TCPClientConnectionStrategy(GameClient *client,
                                                         QTcpSocket *conn,
                                                         QObject *parent)
    : QObject(parent), ClientConnectionStrategy(client), conn(conn) {
  connect(conn, &QTcpSocket::readyRead, this,
          &TCPClientConnectionStrategy::onReadyRead);
}

TCPClientConnectionStrategy::~TCPClientConnectionStrategy() {
  conn->flush();
  conn->close();
  delete conn;
}

void TCPClientConnectionStrategy::onReadyRead() {
  QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
  if (!clientSocket)
    return;

  QByteArray data = clientSocket->readAll();
  for (auto &b : data) {
    if (b != '\n') {
      temp.append(b);
      continue;
    }

    if (temp.toStdString().rfind("error: ", 0) == 0) {
      std::stringstream input(temp.toStdString().substr(7));
      int code;
      input >> code;
      onError(static_cast<ErrorCode>(code));
    } else if (temp.toStdString().rfind("update: ", 0) == 0) {
      std::stringstream input(temp.toStdString().substr(8));
      Game g;
      int dat;
      input >> dat;
      g.game_over = dat == 1;
      input >> dat;
      g.youre_winner = dat == 1;
      input >> dat;
      g.youre_going = dat == 1;
      input >> dat;
      g.reason = static_cast<WinningReason>(dat);

      for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
          input >> dat;
          g.own_field.field[i][j] = static_cast<FieldElement>(dat);
        }
      }
      int sh_amount;
      input >> sh_amount;
      for (int i = 0; i < sh_amount; i++) {
        input >> dat;
        bool is_horizontal = dat == 1;
        int length;
        input >> length;
        int x;
        input >> x;
        int y;
        input >> y;
        g.own_field.ships.push_back(Ship(is_horizontal, length, x, y));
      }

      for (int i = 0; i < GAME_SIZE; i++) {
        for (int j = 0; j < GAME_SIZE; j++) {
          input >> dat;
          g.enemy_field.field[i][j] = static_cast<FieldElement>(dat);
        }
      }
      input >> sh_amount;
      for (int i = 0; i < sh_amount; i++) {
        input >> dat;
        bool is_horizontal = dat == 1;
        int length;
        input >> length;
        int x;
        input >> x;
        int y;
        input >> y;
        g.enemy_field.ships.push_back(Ship(is_horizontal, length, x, y));
      }

      onUpdate(g);
    }

    temp.clear();
  }

  // Parse data from server here:
}

void TCPClientConnectionStrategy::sendHandshake(std::vector<Ship> ships) {
  std::stringstream output;
  output << "handshake: " << ships.size() << " ";
  for (auto &ship : ships) {
    output << (ship.is_horizontal ? 1 : 0) << " " << ship.length << " "
           << ship.x << " " << ship.y << " ";
  }
  output << "\n";

  conn->write(output.str().c_str());
  conn->flush();
}

void TCPClientConnectionStrategy::sendStep(int x, int y) {
  std::stringstream output;
  output << "step: " << x << " " << y << "\n";
  conn->write(output.str().c_str());
  conn->flush();
}

void TCPClientConnectionStrategy::onSurrender() {
  std::stringstream output;
  output << "surrender: \n";
  conn->write(output.str().c_str());
  conn->flush();
}

void TCPClientConnectionStrategy::onUpdate(Game g) {
  this->client->onUpdate(g);
}

void TCPClientConnectionStrategy::onError(ErrorCode error) {
  this->client->onError(error);
}

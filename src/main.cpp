#include <QApplication>

#include <QTcpSocket>
#include <widgets/initgame.h>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  FieldStyle::initStyles();
  InitGame init_game;
  init_game.show();

  /*MyTcpServer server;
  if (!server.listen(QHostAddress::Any, 1234)) {
      std::cout << "Failed to start server" << std::endl;
      return -1;
  }

  std::cout << "Server started on port 1234" << std::endl;*/

  return a.exec();
}

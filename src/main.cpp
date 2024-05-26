#include <QApplication>

#include <QTcpSocket>
#include <widgets/initgame.h>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  FieldStyle::initStyles();
  InitGame init_game;
  init_game.show();

  return a.exec();
}

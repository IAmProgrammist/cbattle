#pragma once

#include <QMainWindow>

#include <models/field.h>
#include <models/ship.h>
#include <widgets/fieldwidgetedit.h>
#include <widgets/gamewindow.h>

namespace Ui {
class InitGame;
}

class InitGame : public QMainWindow {
  Q_OBJECT

public:
  explicit InitGame(QWidget *parent = nullptr);
  ~InitGame();

private:
  bool game_going = false;
  Ui::InitGame *ui;
  GameWindow *game_window;
  QTcpServer *server = nullptr;
  void setupServer();
  void downServer();

protected:
  void showEvent(QShowEvent *event);
  void beginBot();
  void beginCreate();
  void beginJoin();
  void newConnection();
};

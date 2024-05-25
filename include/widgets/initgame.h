#pragma once

#include <QMainWindow>

#include <models/ship.h>
#include <models/field.h>
#include <widgets/fieldwidgetedit.h>
#include <widgets/gamewindow.h>

namespace Ui {
class InitGame;
}

class InitGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit InitGame(QWidget *parent = nullptr);
    ~InitGame();

private:
    Ui::InitGame *ui;
    GameWindow* game_window;
protected:
    void showEvent(QShowEvent* event);
    void beginBot();
};


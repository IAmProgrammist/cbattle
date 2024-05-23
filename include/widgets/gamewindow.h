#pragma once

#include <QMainWindow>

#include <game/client/client.h>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow, public GameClient
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void on_update(Game g);
private:
    Ui::GameWindow *ui;
protected:
    void showEvent(QShowEvent* event);
};

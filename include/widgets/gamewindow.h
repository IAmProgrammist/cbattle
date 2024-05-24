#pragma once

#include <QMainWindow>

#include <game/client/client.h>
#include <widgets/fieldwidgetplayenemy.h>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow, public GameClient
{
    Q_OBJECT

public:
    explicit GameWindow(std::vector<Ship> ships, QWidget *parent = nullptr);
    ~GameWindow();
    void on_update(Game g);
    void init();
private:
    Ui::GameWindow *ui;
    FieldWidgetPlayEnemy* enemy_field = nullptr;
    FieldWidget* own_field = nullptr;
protected:
    Game game;
    std::vector<Ship> ships;
    void showEvent(QShowEvent* event);
};

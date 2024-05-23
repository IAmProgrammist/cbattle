#ifndef INITGAME_H
#define INITGAME_H

#include <QMainWindow>

#include <models/ship.h>
#include <models/field.h>
#include <widgets/fieldwidgetedit.h>

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
protected:
    void showEvent(QShowEvent* event);
};

#endif // INITGAME_H

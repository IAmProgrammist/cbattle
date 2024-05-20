#ifndef INITGAME_H
#define INITGAME_H

#include <QMainWindow>
#include "fieldviewedit.h"
#include "ui_initgame.h"
#include "dump.h"

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
    void showEvent(QShowEvent* event) {
        QMainWindow::showEvent(event);

        if (ui->field->scene()) return;
        auto scene = new FieldViewEdit(ui->field);
        scene->setField(Field::generate_random());

        ui->field->setScene(scene);
    }
};

#endif // INITGAME_H

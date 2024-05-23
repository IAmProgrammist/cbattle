#include <widgets/gamewindow.h>

#include "ui_game.h"

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::GameWindow) {
    ui->setupUi(this);

    //ui->field->setMouseTracking(true);
    //ui->field->setScene(nullptr);
}

GameWindow::~GameWindow(){
    delete ui;
}

void GameWindow::showEvent(QShowEvent* event) {
    QMainWindow::showEvent(event);

    /*if (ui->field->scene()) return;
    auto scene = new FieldWidgetEdit(ui->field);
    scene->setField(Field::generate_random());

    ui->field->setScene(scene);*/
}

void GameWindow::on_update(Game g) {

}

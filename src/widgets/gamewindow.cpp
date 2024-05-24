#include <widgets/gamewindow.h>
#include <game/client/connection.h>
#include <widgets/fieldwidgetplayenemy.h>

#include "ui_game.h"

GameWindow::GameWindow(std::vector<Ship> ships, QWidget *parent) : QMainWindow(parent), ui(new Ui::GameWindow) {
    ui->setupUi(this);
    this->ships = ships;

    ui->enemyfield->setScene(nullptr);
    ui->yourfield->setScene(nullptr);
}

GameWindow::~GameWindow(){
    delete enemy_field;
    delete ui;
}

void GameWindow::showEvent(QShowEvent* event) {
    QMainWindow::showEvent(event);

    if (this->ui->enemyfield->scene() == nullptr) {
        this->enemy_field = new FieldWidgetPlayEnemy(this, ui->enemyfield);
        this->ui->enemyfield->setScene(this->enemy_field);
        this->enemy_field->field = this->game.enemy_field;
        this->enemy_field->redraw();
    }
    if (this->ui->yourfield->scene() == nullptr) {
        this->own_field = new FieldWidget(ui->yourfield);
        this->ui->yourfield->setScene(this->own_field);
        this->own_field->field = this->game.own_field;
        this->own_field->redraw();
    }
}

void GameWindow::on_update(Game g) {
    this->game = g;

    if (this->enemy_field) {
        this->enemy_field->field = this->game.enemy_field;
        this->enemy_field->redraw();
    }
    if (this->own_field) {
        this->own_field->field = this->game.own_field;
        this->own_field->redraw();
    }

    if (this->game.youre_going) {
        this->ui->whose_turn->setText("Ваш ход!");
    } else {
        this->ui->whose_turn->setText("Ход противника!");
    }
}

void GameWindow::init() {
    this->conn->send_handshake(this->ships);
}

#include <widgets/gamewindow.h>
#include <game/client/connection.h>
#include <widgets/fieldwidgetplayenemy.h>
#include <QPen>
#include <QTcpServer>

#include "ui_game.h"

GameWindow::GameWindow(std::vector<Ship> ships, QWidget *parent) : QDialog(parent), ui(new Ui::GameWindow) {
    ui->setupUi(this);
    this->ships = ships;

    ui->enemyfield->setScene(nullptr);
    ui->yourfield->setScene(nullptr);

    this->connect(ui->surrender, &QPushButton::clicked, this, &GameWindow::surrender);
}

GameWindow::~GameWindow(){
    delete enemy_field;
    delete ui;
}

void GameWindow::showEvent(QShowEvent* event) {
    QDialog::showEvent(event);

    if (this->ui->enemyfield->scene() == nullptr) {
        this->enemy_field = new FieldWidgetPlayEnemy(this,
                                                     ui->enemyfield, &FieldStyle::STYLE_PLAY_ENEMY);
        this->ui->enemyfield->setScene(this->enemy_field);
        this->enemy_field->field = this->game.enemy_field;
        this->enemy_field->redraw();
    }
    if (this->ui->yourfield->scene() == nullptr) {
        this->own_field = new FieldWidget(ui->yourfield, &FieldStyle::STYLE_PLAY_SELF);
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

    if (!this->game.game_over) {
        if (this->game.youre_going) {
            this->ui->whose_turn->setText("Ваш ход");
        } else {
            this->ui->whose_turn->setText("Ход противника");
        }
    } else {
        if (this->game.youre_winner) {
            if (this->game.reason == WinningReason::FAIR)
                this->ui->whose_turn->setText("Вы победили");
            else if (this->game.reason == WinningReason::SURRENDER)
                this->ui->whose_turn->setText("Противник сдался");
        } else {
            this->ui->whose_turn->setText("Вы проиграли");
        }
    }
}

void GameWindow::on_error(ErrorCode error) {
    switch (error) {
    case NO_HANDSHAKE:
    case BAD_HANDSHAKE:
        handshake_ok = false;
        this->close();
        break;
    default:
        break;
    }
}

void GameWindow::init() {
    this->handshake_ok = true;
    this->conn->send_handshake(this->ships);
}

void GameWindow::closeEvent(QCloseEvent* event) {
    this->on_surrender();
}

void GameWindow::surrender() {
    this->close();
}

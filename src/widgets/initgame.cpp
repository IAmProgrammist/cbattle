#include <widgets/initgame.h>

#include <widgets/gamewindow.h>
#include <game/gamebuilder.h>
#include <game/client/botclient.h>

#include "ui_initgame.h"

InitGame::InitGame(QWidget *parent) : QMainWindow(parent), ui(new Ui::InitGame) {
    ui->setupUi(this);

    ui->field->setMouseTracking(true);
    ui->field->setScene(nullptr);

    this->connect(ui->begin_bot, &QPushButton::clicked, this, &InitGame::beginBot);
}

InitGame::~InitGame(){
    delete ui;
}

void InitGame::showEvent(QShowEvent* event) {
    QMainWindow::showEvent(event);

    if (ui->field->scene()) return;
    auto scene = new FieldWidgetEdit(ui->field);
    scene->setField(Field::generate_random());

    ui->field->setScene(scene);
}

void InitGame::beginBot() {
    auto game_view = new GameWindow(reinterpret_cast<FieldWidgetEdit*>(ui->field->scene())->field.ships);
    auto gamebuilder = new GameBuilder();
    auto bot_view = new BotGameClient();
    auto k = gamebuilder->playing(game_view).vs(bot_view);
    k.begin();

    this->hide();
    game_view->show();
}

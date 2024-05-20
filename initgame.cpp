#include "initgame.h"
#include "ui_initgame.h"
#include "fieldview.h"

InitGame::InitGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InitGame)
{
    ui->setupUi(this);

    ui->field->setMouseTracking(true);
    ui->field->setScene(nullptr);
}

InitGame::~InitGame()
{
    delete ui;
}

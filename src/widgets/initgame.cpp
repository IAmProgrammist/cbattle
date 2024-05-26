#include <widgets/initgame.h>

#include <widgets/gamewindow.h>
#include <game/gamebuilder.h>
#include <game/client/botclient.h>
#include <game/client/tcpconnectionstrategy.h>

#include <sstream>
#include <QTcpSocket>
#include <QNetworkInterface>

#include "ui_initgame.h"

InitGame::InitGame(QWidget *parent) : QMainWindow(parent), ui(new Ui::InitGame) {
    ui->setupUi(this);

    ui->field->setMouseTracking(true);
    ui->field->setScene(nullptr);

    this->connect(ui->begin_bot, &QPushButton::clicked, this, &InitGame::beginBot);
    this->connect(ui->begin_create, &QPushButton::clicked, this, &InitGame::beginCreate);
    this->connect(ui->begin_join, &QPushButton::clicked, this, &InitGame::beginJoin);
}

void InitGame::beginJoin() {
    if (game_going) return;
    if (this->server) return;
    auto ip = ui->join_ip->toPlainText().toStdString();
    auto port = ui->join_port->toPlainText().toInt();

    QTcpSocket* socket = new QTcpSocket(this);
    socket->connectToHost(QHostAddress(QString::fromStdString(ip)), port);

    if (socket->waitForConnected()) {
        game_window = new GameWindow(reinterpret_cast<FieldWidgetEdit*>(ui->field->scene())->field.ships);
        game_window->conn = new ClientConnection(new TCPClientConnectionStrategy(game_window, socket, this));

        this->hide();
        game_going = true;
        game_window->init();
        game_window->exec();
        this->show();

        delete game_window->conn;
        delete game_window;

        game_going = false;
    }
}

void InitGame::newConnection() {
    QTcpSocket* socket = this->server->nextPendingConnection();
    if (game_going) {
        socket->close();
        return;
    }

    game_window = new GameWindow(reinterpret_cast<FieldWidgetEdit*>(ui->field->scene())->field.ships);
    auto gamebuilder = new GameBuilder();
    auto k = gamebuilder->playing(game_window).vs(socket);
    k.begin();

    if (game_window->handshake_ok) {
        this->hide();
        game_going = true;
        game_window->exec();
    }
    this->show();

    gamebuilder->destroy();
    delete gamebuilder;
    delete game_window;
    game_going = false;
}

void InitGame::downServer() {
    if (!this->server) return;
    this->server->close();
    delete this->server;
    this->server = nullptr;
    this->ui->begin_bot->setEnabled(true);
    this->ui->begin_join->setEnabled(true);

    this->ui->begin_create->setText("Создать игру");
}

void InitGame::setupServer() {
    if (this->server) return;
    std::stringstream btntext;
    btntext << "Порт для подключения: ";
    this->server = new QTcpServer(this);
    this->server->listen(QHostAddress::LocalHost);
    btntext << this->server->serverPort();
    this->ui->begin_create->setText(QString::fromStdString(btntext.str()));
    this->ui->begin_bot->setEnabled(false);
    this->ui->begin_join->setEnabled(false);

    this->connect(this->server, &QTcpServer::newConnection, this, &InitGame::newConnection);
}

void InitGame::beginCreate() {
    if (this->server) {
        downServer();
    } else {
        setupServer();
    }
}

InitGame::~InitGame(){
    delete ui;
}

void InitGame::showEvent(QShowEvent* event) {
    QMainWindow::showEvent(event);

    if (ui->field->scene()) return;
    auto scene = new FieldWidgetEdit(ui->field);
    scene->setField(Field::generateRandom());

    ui->field->setScene(scene);
}

void InitGame::beginBot() {
    if (game_going) return;
    if (this->server) return;
    game_window = new GameWindow(reinterpret_cast<FieldWidgetEdit*>(ui->field->scene())->field.ships);
    auto gamebuilder = new GameBuilder();
    auto bot_view = new BotGameClient();
    auto k = gamebuilder->playing(game_window).vs(bot_view);
    k.begin();

    if (game_window->handshake_ok) {
        this->hide();
        game_going = true;
        game_window->exec();
    }
    this->show();

    gamebuilder->destroy();
    delete gamebuilder;
    delete game_window;
    delete bot_view;
    game_going = false;
}

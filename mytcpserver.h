#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class MyTcpServer : public QTcpServer
{
    Q_OBJECT

public:
    MyTcpServer(QObject *parent = nullptr) : QTcpServer(parent) {}

protected:
    void incomingConnection(qintptr socketDescriptor) override {
        QTcpSocket* clientSocket = new QTcpSocket(this);
        clientSocket->setSocketDescriptor(socketDescriptor);

        connect(clientSocket, &QTcpSocket::readyRead, this, &MyTcpServer::onReadyRead);
        connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);

        qDebug() << "Client connected: " << clientSocket->peerAddress().toString();

        // Handle the incoming connection
    }

private slots:
    void onReadyRead() {
        QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
        if (!clientSocket)
            return;

        // Read data from the client socket
        QByteArray data = clientSocket->readAll();
        qDebug() << "Received data: " << data;

        // Handle the received data
    }
};

#endif // MYTCPSERVER_H

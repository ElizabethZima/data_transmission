#include "tcpclient.h"
#include <QByteArray>
#include <QHostAddress>
#include <QTcpSocket>
#include <iostream>
#include <QCoreApplication>


TcpClient::TcpClient(quint16 PORT, QByteArray _data, QObject *p) :
        QObject(p), data(_data)
{
    tSocket = new QTcpSocket(this);
    std::cout << "--- Connect to Host ---" << std::endl;
    /* Отправляем запрос на подключение к серверу */
    tSocket->connectToHost(QHostAddress::LocalHost, PORT);
    /* ------- Соединить сигнал и слот ------- */
    /* Отправить сообщение, как только вы подключитесь к серверу */
    connect(tSocket, SIGNAL(connected()),this, SLOT(send_msg()));
    /* сервер читает, если отвечает */
    connect(tSocket, SIGNAL(readyRead()),this, SLOT(read_msg()));
    /* сервер отправляет запрос при разрыве соединения */
    connect(tSocket, SIGNAL(disconnected()),this, SLOT(end_connect()));
}

TcpClient::~TcpClient()
{
    tSocket->close();
    tSocket->deleteLater();
}

void TcpClient::send_msg()
{
    std::cout << "--- Successfully Connected ---\n"
              << "--- Sending Message ---"
              << std::endl;

    /* Отправить сообщение */
    tSocket->write(data);
}

void TcpClient::read_msg()
{
    /* Прочитать информацию */
    QByteArray ba = tSocket->readAll();
    std::cout << ba.data() << std::endl;

}

void TcpClient::end_connect()
{
    std::cout << "--- Connection Ended Client---" << std::endl;

}
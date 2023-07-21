#include "tcpserver.h"
#include <QByteArray>
#include <QHostAddress>
#include <iostream>
#include "tcpserver.h"

const quint16 PORT = 2333;

TcpServer::TcpServer(QTcpServer *p) :
        QTcpServer(p)
{
    tServer = new QTcpServer;
    tSocket = new QTcpSocket;
    /* Порт прослушивания */
    if(tServer->listen(QHostAddress::Any, PORT))
        std::cout << "--- Linsting to Port ---" << std::endl;
    else
        std::cout << "*** FAIL LISTING ***" << std::endl;
    /* Обработка нового запроса на подключение */
    connect(tServer, SIGNAL(newConnection()),this, SLOT(accept_connection()));
}

TcpServer::~TcpServer()
{
    delete tServer;
    delete tSocket;
}

void TcpServer::accept_connection()
{
    std::cout << "--- Accept Connection ---" << std::endl;
    /* Сервер подключает свой сокет к клиентскому сокету */
    tSocket = tServer->nextPendingConnection();

    /* Socket читает и отвечает, как только получает информацию */
    connect(tSocket, SIGNAL(readyRead()),
            this, SLOT(read_and_reply()));
}

void TcpServer::read_and_reply()
{
    std::cout << "--- Read Message ---" << std::endl;
    /* Прочитать информацию */
    QByteArray ba = tSocket->readAll();
    std::cout << ba.data() << std::endl;
    std::cout << "--- Reply ---" << std::endl;
    /* Ответить */
    tSocket->write("Nice day");
    tSocket->close();
}

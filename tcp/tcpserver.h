#ifndef TCP2_TCPSERVER_H
#define TCP2_TCPSERVER_H


#include <QTcpServer>
#include <QTcpSocket>

class TcpServer : QTcpServer
{
Q_OBJECT

public:
    TcpServer(QTcpServer *p = nullptr);
    ~TcpServer();

public slots:
    void accept_connection(); // Обрабатываем запрос на подключение
    void read_and_reply(); // читаем сообщение и отвечаем, затем отключаемся

private:
    QTcpServer *tServer;
    QTcpSocket *tSocket;
};


#endif //TCP2_TCPSERVER_H

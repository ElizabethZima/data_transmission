#ifndef TCP_TCPSERVER_H
#define TCP_TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>

class TcpServer : QTcpServer
{
Q_OBJECT

public:
    TcpServer(quint16 PORT, QTcpServer *p = 0);
    ~TcpServer();

public slots:
    void accept_connection(); // Обрабатываем запрос на подключение
    void read_and_reply(); // читаем сообщение и отвечаем, затем отключаемся

private:
    QTcpServer *tServer;
    QTcpSocket *tSocket;
};

#endif //TCP_TCPSERVER_H

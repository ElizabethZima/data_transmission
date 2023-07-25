
#ifndef TCP2_TCPCLIENT_H
#define TCP2_TCPCLIENT_H


#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject
{
Q_OBJECT

public:
    TcpClient(QObject *p = 0);
    ~TcpClient();

public slots:
    void send_msg(); // отправляем сообщение на сервер
    void read_msg(); // Считываем информацию, возвращаемую сервером
    void end_connect(); // Запрос после отключения

private:
    QTcpSocket *tSocket;
};

#endif //TCP2_TCPCLIENT_H

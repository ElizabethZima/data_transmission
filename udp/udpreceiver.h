#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H
#include <QObject>
#include <QUdpSocket>


class UdpReceiver : public QObject{

Q_OBJECT


public:

    UdpReceiver(QObject *p = nullptr);

    ~UdpReceiver() ;
public slots:

    void receive();
private:

    QUdpSocket *uSocket;

};

#endif // UDPRECEIVER_H
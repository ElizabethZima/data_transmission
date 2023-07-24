#include "udpreceiver.h"
#include <QByteArray>
#include <iostream>
extern const quint16 PORT;

UdpReceiver::UdpReceiver( QObject *p) :

QObject(p){

        uSocket = new QUdpSocket;

        uSocket->bind(QHostAddress("127.0.0.1"), PORT);

        connect(uSocket, SIGNAL(readyRead()), this, SLOT(receive()));
}
        UdpReceiver::~UdpReceiver(){

    delete uSocket;
}


    void UdpReceiver::receive(){

    QByteArray ba;

    std::cout << " ";

    while(uSocket->hasPendingDatagrams())

    {

        ba.resize(uSocket->pendingDatagramSize());
           uSocket->readDatagram(ba.data(), ba.size());


        std::cout << ba.data() << std::endl;

    }

}

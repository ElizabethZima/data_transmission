#include <QCoreApplication>
#include <QDebug>
#include <QTime>
#include <iostream>
#include "tcp/tcpclient.h"
#include "tcp/tcpserver.h"
//#include "udp/udpreceiver.h"
#include "configReader/configReader.h"

const extern quint16 PORT = 5000;

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    configReader::print("C:/Users/Студент/CLionProjects/tcpudp/config.json");

//
//    delay();

    ///UDP///

//    UdpReceiver ur;
//
//    QUdpSocket qus;
//
//    qus.bind(QHostAddress("127.0.0.1"), PORT+1);
//
//    QByteArray msg = "Hello world!";
//
//    std::cout << "--- Sender ---" << std::endl;
//
//    for(int i = 0; i < 10; ++i)
//        qus.writeDatagram(msg, QHostAddress("127.0.0.1"), PORT);
//
//
//    std::cout << "--- Recevier ---" << std::endl;

    return QCoreApplication::exec();
}

#include "main.moc"
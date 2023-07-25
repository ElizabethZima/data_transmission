#include <QCoreApplication>
#include <QDebug>
#include <QTime>
#include <iostream>
#include <QUdpSocket>
#include "tcp/tcpclient.h"
#include "tcp/tcpserver.h"
#include "udp/udpreceiver.h"
#include "configReader/configReader.h"
//#include "udp/udpreceiver.h"
//#include "configReader/configReader.h"

//extern quint16 PORT = 5000;

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void tcp() {
        std::cout << "--- TCP Client ---" << std::endl;
        TcpClient tc;



        std::cout << "--- TCP Server ---" << std::endl;
        TcpServer ts;
    tc.send_msg();
        ts.read_and_reply();
        tc.send_msg();

};



int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    configReader::print("C:/Users/Студент/CLionProjects/tcpudp/config.json");
 //  tcp();


//
//    delay();

    ///UDP///




    return QCoreApplication::exec();
}

#include "main.moc"
#include <QCoreApplication>
#include <QDebug>
#include <QTime>
#include <iostream>
#include <QUdpSocket>
//#include "tcp/tcpclient.h"
//#include "tcp/tcpserver.h"
//#include "udp/udpreceiver.h"
#include "configReader/configReader.h"



int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    configReader::print("C:/Users/Студент/CLionProjects/tcpudp/config.json");

    return QCoreApplication::exec();
}

#include "main.moc"
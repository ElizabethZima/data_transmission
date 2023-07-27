#include <QCoreApplication>
#include <QDebug>
#include <QTime>
#include <iostream>
#include <QUdpSocket>
#include "configReader/configReader.h"


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    configReader::print("C:/tcpudp/config.json");

    a.exit(0);
    return 0;
}

//#include "main.moc"
#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include "tcpclient.h"
#include "tcpserver.h"


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    ///TCP ///
    std::cout << "--- TCP Client ---" << std::endl;
    TcpClient tc;

    std::cout << "--- TCP Server ---" << std::endl;
    TcpServer ts;


    return QCoreApplication::exec();
}

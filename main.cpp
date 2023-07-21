#include <QCoreApplication>
#include <QDebug>
#include <QTime>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <iostream>
#include "tcp/tcpclient.h"
#include "tcp/tcpserver.h"
#include "udp/udpreceiver.h"

const extern quint16 PORT = 5000;

void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}



void readJsonFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open the JSON file.";
        return;
    }

    // Чтение содержимого файла и его парсинг как JSON
    QByteArray jsonData = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(jsonData);

    if (document.isNull()) {
        qWarning() << "Failed to parse the JSON file.";
        return;
    }

    // Теперь вы можете работать с данными из файла JSON
    QJsonObject jsonObject = document.object();

    // Пример доступа к значениям по ключам:
    if (jsonObject.contains("udp")) {
        QJsonObject udpObject = jsonObject["udp"].toObject();
        QString host = udpObject["host"].toString();
        int port= udpObject["port"].toInt();

        qDebug() << "UDP Host: " << host;
        qDebug() << "UDP Port: " << port;
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    readJsonFile("C:/Users/Студент/CLionProjects/tcpudp/config.json");

    ///TCP ///
    std::cout << "--- TCP Client ---" << std::endl;
    TcpClient tc;

    std::cout << "--- TCP Server ---" << std::endl;
    TcpServer ts;

    delay();

    ///UDP///




    UdpReceiver ur;

    QUdpSocket qus;

    qus.bind(QHostAddress("127.0.0.1"), PORT+1);

    QByteArray msg = "Hello world!";

    std::cout << "--- Sender ---" << std::endl;

    for(int i = 0; i < 10; ++i)
        qus.writeDatagram(msg, QHostAddress("127.0.0.1"), PORT);


    std::cout << "--- Recevier ---" << std::endl;




    return QCoreApplication::exec();
}

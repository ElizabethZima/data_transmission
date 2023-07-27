#ifndef TCPUDP_CONFIGREADER_H
#define TCPUDP_CONFIGREADER_H

#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include "../udp/udpreceiver.h"
#include "../tcp/tcpserver.h"
#include "../tcp/tcpclient.h"
#include "QtSerialPort/QSerialPort"

void delay(int i){

    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, i);

}

void udp(UdpReceiver& ur, QUdpSocket& qus, qint16 PORT, QByteArray& msg){

    qus.bind(QHostAddress("127.0.0.1"), PORT);

    qDebug() << "--- Sender ---" ;
    qDebug() << msg << "\n";

    qus.writeDatagram(msg, QHostAddress("127.0.0.1"), PORT);


    std::cout << "--- Recevier ---" << std::endl;
    ur.receive();
}


void comport(QString port1, QString port2, QByteArray& msg){
    // Создаем объект класса QSerialPort для работы с портом
    QSerialPort serial;
    QSerialPort serial2;

    // Устанавливаем имя COM-порта (например, "COM1" или "/dev/ttyUSB0")
    serial.setPortName(port1);
    serial2.setPortName(port2);


    // Открываем порт в режиме чтения и записи
    if (!serial2.open(QIODevice::ReadWrite)) {
        qDebug() << "Port opening error 1:" << serial2.errorString();
        return;
    }

    // Открываем порт в режиме чтения и записи
    if (!serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Port opening error 2:" << serial.errorString();
        return;
    }

    // Настраиваем параметры соединения (скорость передачи данных, биты данных и т.д.)
    serial.setBaudRate(QSerialPort::Baud9600);
    serial2.setBaudRate(QSerialPort::Baud9600);



    // Записываем данные в порт
    qDebug() << "Writing:";
    if(serial.write(msg) == -1)
        qDebug()<< "Error when sending data";
    else
        qDebug().noquote() << msg;

    delay(100);
    // Читаем данные из порта
    qDebug() << "Reading:";
    serial2.waitForReadyRead(100);
    QByteArray data = serial2.readAll();
    qDebug() << data << "\n";


    // Закрываем порт после использования
    serial.close();
    serial2.close();
}

class configReader {

private :


    static void readJson(QJsonObject jsonObject) {

    //count of sokets
        int count = 0;

        /*     Reading CONFIG INFO    */

        if (jsonObject.contains("config")) {

            QJsonObject confObject = jsonObject["config"].toObject();

            if(confObject.contains("count")){

                count = confObject["count"].toInt();

            }
            else{

                std::cout << "wrong config information\n";
                return;

            }

        }
        else{
            std::cout << "wrong config information\n";
            return;
        }

        /*     reading json data   */

        for(int i = 0; i < count ; ++i){

            QJsonObject newObject = jsonObject[QString::number(i)].toObject();


            /*    parse UDP  */

            if (newObject.contains("udp")) {

                QJsonObject udpObject = newObject["udp"].toObject();
                QString host = udpObject["host"].toString();
                int port = udpObject["port"].toInt();
                qint16 delaytime = udpObject["timeout_seconds"].toInt();

                QByteArray msg;
                msg.append(udpObject["message"].toString());
                delay(delaytime);

                qDebug() << "UDP Host: " << host;
                qDebug() << "UDP Port: " << port;

                delay(delaytime);

                UdpReceiver ur(port);
                QUdpSocket qus;
                udp(ur, qus, port, msg);
                qus.close();

            }

            /*    parse TCP    */

            else if (newObject.contains("tcp")) {

                QJsonObject tcpObject = newObject["tcp"].toObject();
                QString host = tcpObject["host"].toString();
                qint16 port = tcpObject["port"].toInt();
                qint16 delaytime = tcpObject["timeout_seconds"].toInt();
                QByteArray msg;
                msg.append(tcpObject["message"].toString());

                qDebug() << "TCP Host: " << host;
                qDebug() << "TCP Port: " << port;
                delay(delaytime);

                std::cout << "--- TCP Client ---" << std::endl;
                TcpClient tc(port, msg);

                std::cout << "--- TCP Server ---" << std::endl;
                TcpServer ts(port);

                delay(delaytime);

            }

            else if(newObject.contains("com")){
                qDebug() << "Comport";

                QJsonObject comObject = newObject["com"].toObject();
                QString port1 = comObject["port1"].toString();
                QString port2 = comObject["port2"].toString();
                qint16 delaytime = comObject["timeout_seconds"].toInt();
                QByteArray msg;
                msg.append(comObject["message"].toString());

                qDebug() << "PORT 1 : " << port1;
                qDebug() << "PORT 2 : " << port2 << "\n";
                delay(delaytime);
                comport(port1, port2,msg);
            }
            else{
                qDebug() << "Unknown";
            }

            delay(2000);

        }

    }

public:

    static void print(const QString& filePath){

        QFile file(filePath);

        //Fail parsing
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

        readJson(jsonObject);
    }

};

#endif //TCPUDP_CONFIGREADER_H

#ifndef TCPUDP_CONFIGREADER_H
#define TCPUDP_CONFIGREADER_H

#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

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

                qDebug() << "UDP Host: " << host;
                qDebug() << "UDP Port: " << port;
            }

            /*    parse TCP    */

            else if (newObject.contains("tcp")) {

                QJsonObject tcpObject = newObject["tcp"].toObject();
                QString host = tcpObject["host"].toString();
                qint16 port = tcpObject["port"].toInt();

                qDebug() << "TCP Host: " << host;
                qDebug() << "TCP Port: " << port;


                ///TCP ///
                std::cout << "--- TCP Client ---" << std::endl;
                TcpClient tc(port);


                std::cout << "--- TCP Server ---" << std::endl;
                TcpServer ts(port);
                ts.read_and_reply();
            }

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

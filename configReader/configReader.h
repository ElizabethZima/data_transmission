#ifndef TCPUDP_CONFIGREADER_H
#define TCPUDP_CONFIGREADER_H


#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

class configReader {

public :
    static void print(const QString& filePath){

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

        if (jsonObject.contains("tcp")) {
            QJsonObject udpObject = jsonObject["tcp"].toObject();
            QString host = udpObject["host"].toString();
            int port = udpObject["port"].toInt();

            qDebug() << "UDP Host: " << host;
            qDebug() << "UDP Port: " << port;
        }
    }

};


#endif //TCPUDP_CONFIGREADER_H

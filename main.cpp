#include <QCoreApplication>
#include "configReader/configReader.h"


int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    configReader::print("C:\\Users\\Студент\\CLionProjects\\data_transmission\\config.json");

    a.exit(0);
    return 0;
}

//#include "main.moc"
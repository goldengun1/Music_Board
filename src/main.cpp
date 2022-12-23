#include "mainwindow.h"
#include "headers/utils.h"
#include <QApplication>
#include <QFile>
#include<QVector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString stylePath = ":/src/teme/Darkeum.qss";

    QString styleSheetData = QString(Utils::readJsonFromFile(stylePath));
      a.setStyleSheet(styleSheetData);


    MainWindow w;
    w.show();
    return a.exec();
}

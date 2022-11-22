#include "mainwindow.h"
#include "headers/utlis.h"
#include <QApplication>
#include<QFile>
#include<QVector>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //set the style sheet
    QString stylePath = "/Darkeum.qss";

    QString styleSheetData = QString(Utlis::readJsonFromFile(stylePath));
      a.setStyleSheet(styleSheetData);




    MainWindow w;
    w.show();
    return a.exec();
}

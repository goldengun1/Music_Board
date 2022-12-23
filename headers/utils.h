#ifndef UTILS_H
#define UTILS_H

#include <QByteArray>
#include <QString>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>



class Utils: public QObject
{
    Q_OBJECT
public:
    Utils();

    static QByteArray readJsonFromFile(QString &fileName);

};

#endif // UTILS_H

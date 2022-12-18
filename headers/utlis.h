#ifndef UTLIS_H
#define UTLIS_H

#include <QByteArray>
#include <QString>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <QColor>



class Utlis: public QObject
{
    Q_OBJECT
public:
    Utlis();

    static QByteArray readJsonFromFile(QString &fileName);
    static QColor randomColor();

};

#endif // UTLIS_H

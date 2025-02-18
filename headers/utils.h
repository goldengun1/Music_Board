#pragma once

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
#include <QRandomGenerator>

class Utils: public QObject
{
    Q_OBJECT
public:
    Utils();

    constexpr static const qreal TIMELINE_SCALE = 3.0; // How much ms is each graphical unit of measure.
    constexpr static const qreal TRACK_HEIGHT = 30.0;

    static QByteArray readJsonFromFile(QString &fileName);
    static QColor randomColor();
    static qreal MilisecondsToPixel(quint64 duration);

};

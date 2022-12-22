#include "utils.h"

#include <QRandomGenerator>

Utils::Utils()
{

}
QByteArray Utils::readJsonFromFile(QString &fileName)
{
    QFile file(fileName);
    QByteArray data = QByteArray("");
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << file.errorString();
    } else {
        data = file.readAll();
    }

    return data;
}

QColor Utils::randomColor() {
    auto r = QRandomGenerator::global()->bounded(255);
    auto g = QRandomGenerator::global()->bounded(255);
    auto b = QRandomGenerator::global()->bounded(255);

     return QColor::fromRgb(r, g, b);
}

qreal Utils::MilisecondsToPixel(quint64 duration) {
    return (qreal)duration / Utils::TIMELINE_SCALE;
}


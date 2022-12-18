#include "utlis.h"

#include <QRandomGenerator>

Utlis::Utlis()
{

}
QByteArray Utlis::readJsonFromFile(QString &fileName)
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

QColor Utlis::randomColor() {
    auto r = QRandomGenerator::global()->bounded(255);
    auto g = QRandomGenerator::global()->bounded(255);
    auto b = QRandomGenerator::global()->bounded(255);

     return QColor::fromRgb(r, g, b);
}

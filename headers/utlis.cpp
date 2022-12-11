#include "utlis.h"

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

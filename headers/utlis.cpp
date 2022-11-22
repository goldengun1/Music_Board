#include "utlis.h"

Utlis::Utlis()
{

}
QByteArray Utlis::readJsonFromFile(QString &fileName)
{
    QDir dir("../05-muzicka-tabla/src/teme");
    QString path = dir.absolutePath() + fileName;

    QFile file(path);
    QByteArray data = QByteArray("");
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << file.errorString();
    } else {
        data = file.readAll();
    }

    return data;
}

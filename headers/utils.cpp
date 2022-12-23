#include "utils.h"

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

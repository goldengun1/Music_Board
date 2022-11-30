#include "matrix.h"
#include <QFile>
#include <QTextStream>

void
Matrix::Clear(void)
{
    timeline.clear();
}

uint32_t
Matrix::Append(std::pair<uint32_t, sid> mark)
{
    return Append(mark.first, mark.second);
}

uint32_t
Matrix::Append(uint32_t marktime, sid marksound)
{
    return timeline.emplace_back(marktime, marksound).first;
}

void Matrix::Export(const QString & path)
{
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::NewOnly | QIODevice::Text)) {
        // @TODO: handle error
        qDebug("Failed to open file");
        return;
    }

    QTextStream out(&file);

    for (auto &pair : timeline) {
        out << pair.first << ' ' << pair.second << '\n';
    }

    file.close();
}

Matrix Matrix::Import(const QString & path) {

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // @TODO: handle error
        throw "Unable to open file.";
    }

    QTextStream in(&file);

    Matrix m;
    uint32_t markTime;
    sid markSound;
    while (!in.atEnd()) {
        in >> markTime >> markSound;
        in.seek(in.pos() + 1); // Preskacemo `\n` karaktere.
        m.Append(markTime, markSound);
    }

    file.close();

    return m;
}

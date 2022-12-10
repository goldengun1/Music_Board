#include "matrix.h"
#include <QFile>
#include <QTextStream>

void
Matrix::Clear(void)
{
    timeline = std::priority_queue<mark_t, std::vector<mark_t>, std::greater<mark_t>>();
}

uint32_t
Matrix::Append(std::pair<uint32_t, sid> mark)
{
    return Append(mark.first, mark.second);
}

uint32_t
Matrix::Append(uint32_t marktime, sid marksound)
{
    return timeline.emplace(marktime, marksound), marktime;
}

void Matrix::Export(const QString & path) const
{
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::NewOnly | QIODevice::Text)) {
        // @TODO: handle error
        qDebug("Failed to open file");
        return;
    }

    QTextStream out(&file);

    std::priority_queue<mark_t, std::vector<mark_t>, std::greater<mark_t>> buffer(timeline);
    while (!buffer.empty())
    {
       std::pair<uint32_t, sid> pair = buffer.top();

       out << pair.first << ' ' << pair.second << '\n';
       buffer.pop();
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

bool Matrix::Empty() const {
    return timeline.empty();
}

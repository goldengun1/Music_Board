#include "matrix.h"
#include <QFile>
#include <QTextStream>

void
Matrix::Clear(void)
{
    timeline = std::priority_queue<mark_t, std::vector<mark_t>, std::greater<mark_t>>();
}

marktype_t
Matrix::Append(mark_t mark)
{
    return Append(mark.first.first, mark.first.second, mark.second), mark.first.second;
}

marktype_t
Matrix::Append(uint32_t marktime, marktype_t marktype, sid marksound)
{
    return timeline.emplace(std::make_pair(marktime, marktype), marksound), marktype;
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
        std::pair<markinfo_t, sid>      pair1 = buffer.top();
        std::pair<uint32_t, marktype_t> pair2 = pair1.first;

        // time, type, sid
        out << pair2.first << ' ' << pair2.second << ' ' << pair1.second << '\n';
        buffer.pop();
    }

    file.close();
}

std::pair<Matrix, uint32_t> Matrix::Import(const QString & path) {

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // @TODO: handle error
        throw "Unable to open file.";
    }

    QTextStream in(&file);

    Matrix m;
    uint32_t markTime;
    uint32_t markTypeint;
    sid markSound;
    uint32_t matrixDuration;
    while (!in.atEnd())
    {
        in >> markTime >> markTypeint >> markSound;
        in.seek(in.pos() + 1); // Preskacemo `\n` karaktere.
        m.Append(markTime, static_cast<marktype_t>(markTypeint), markSound);
        if (static_cast<marktype_t>(markTypeint) == MARK_REC_STOP)
            matrixDuration = markTime;
    }

    file.close();

    return std::make_pair(m, matrixDuration);
}

bool Matrix::Empty() const {
    return timeline.empty();
}

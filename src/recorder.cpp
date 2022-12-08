#include <QDebug>
#include "recorder.h"

void
Recorder::Start(void)
{
    Rewind();
    recording = true;
}

marktype_t
Recorder::Mark(sid sound, marktype_t type)
{
    const qint64 time = stopwatch.elapsed();

    qDebug() << "Mark at " << time << ".";
    return matrix.Append(time, type, sound);
}

void
Recorder::Rewind(void)
{
    stopwatch.restart();
}

Matrix
Recorder::Stop(void)
{
    recording = false;
    return matrix;
}

void
Recorder::Reset(void)
{
    matrix.Clear();
    Rewind();
}

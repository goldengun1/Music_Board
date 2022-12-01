#include <QDebug>
#include "recorder.h"

void
Recorder::Start(void)
{
    Rewind();
    recording = true;
}

uint64_t
Recorder::Mark(sid sound)
{
    const qint64 time = stopwatch.elapsed();

    qDebug() << "Mark at " << time << ".";
    return (last = matrix.Append(time, sound));
}

void
Recorder::Rewind(void)
{
    stopwatch.restart();
}

std::pair<uint64_t, Matrix>
Recorder::Stop(void)
{
    recording = false;
    return { last, matrix };
}

void
Recorder::Reset(void)
{
    matrix.Clear();
    Rewind();
    last = 0;
}

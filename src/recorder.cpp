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
    if(firstRecordingDuration == 0) {
        firstRecordingDuration = stopwatch.elapsed();
        Mark(0, MARK_REC_STOP);
    }
    recording = false;
    return matrix;
}

void Recorder::handleMatrixEnd()
{
    if(loopRecording){
        Rewind();
    }
}

void
Recorder::Reset(void)
{
    firstRecordingDuration = 0;
    matrix.Clear();
    Rewind();
}

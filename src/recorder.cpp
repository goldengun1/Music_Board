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
    if(recording){
        auto time = stopwatch.elapsed();
        if(firstRecordingDuration == 0) {
            firstRecordingDuration = time;
            longestRecordingDuration = time;
        }
        else if(time > longestRecordingDuration) {
            longestRecordingDuration = time;
        }
        Mark(0, MARK_REC_STOP);
        recording = false;
    }
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
    longestRecordingDuration = 0;
    matrix.Clear();
    Rewind();
    recording = false;
}

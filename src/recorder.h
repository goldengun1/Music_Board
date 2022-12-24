#pragma once

#include <QElapsedTimer>
#include <QDebug>
#include "matrix.h"
#include "soundbank.h" // for 'sid' type.

//
// Construct matrix with timestamps.
//
class Recorder: public QObject
{
    Q_OBJECT

    Matrix        matrix;
    QElapsedTimer stopwatch;
    bool          recording {false};

public:
    void       Start(void);           // Restart stopwatch and start (internally) counting time passed.
    marktype_t Mark(sid, marktype_t); // New mark with current stopwatch time and given sound id. Return current time.
    void       Rewind(void);
    void       Reset(void);

    bool Recording(void) const { return recording; }

    void Stop(void); // Return last mark's time and recorded matrix.

    bool   loopRecording = false;
    qint64 firstRecordingDuration = 0;
    qint64 longestRecordingDuration = 0;

    void setMatrix(const Matrix &newMatrix);
    Matrix getMatrix() { return matrix; }

public slots:
    void handleMatrixEnd();
};

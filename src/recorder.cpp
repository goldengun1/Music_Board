#include "recorder.h"

void
Recorder::Start(void)
{
    matrix.Clear();
    stopwatch.restart();
    last = 0;
}

uint64_t
Recorder::Mark(sid sound)
{
    return (last = matrix.Append(stopwatch.elapsed(), sound));
}

Matrix
Recorder::Stop(void)
{
    return matrix;
}

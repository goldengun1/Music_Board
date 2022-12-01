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

void
Recorder::Rewind(void)
{
    stopwatch.restart();
}

std::pair<uint64_t, Matrix>
Recorder::Stop(void)
{
    return { last, matrix };
}

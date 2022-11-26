#include "recorder.h"

void
Recorder::Start(void)
{
    matrix.clear();
    stopwatch.restart();
    last = 0;
}

uint64_t
Recorder::Mark(sid sound)
{
    return matrix.emplace_back((last = stopwatch.elapsed()), sound).first;
}

std::pair<uint64_t, matrix_t>
Recorder::Stop(void)
{
    return std::make_pair(last, matrix);
}

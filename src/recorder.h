#pragma once

#include <QElapsedTimer>
#include "matrix.h"
#include "soundbank.h" // for 'sid' type.

using matrix_t = std::vector<std::pair<uint64_t, sid>>; // This should be its own Matrix class.

//
// Construct matrix with timestamps.
//
class Recorder
{
    Matrix        matrix;
    uint64_t      last;      // Last mark time.
    QElapsedTimer stopwatch;

public:
    void     Start(void); // Restart stopwatch and start (internally) counting time passed.
    uint64_t Mark(sid);   // New mark with current stopwatch time and given sound id. Return current time.
    void     Rewind(void);

    [[nodiscard("RECORDED MATRIX IS NOT USED")]]
    std::pair<uint64_t, Matrix> Stop(void); // Return last mark's time and recorded matrix.
};

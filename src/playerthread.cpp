#include "playerthread.h"

#include <iostream>

PlayerThread::PlayerThread(const Matrix& matrix, QObject *parent) : QThread(parent), matrix{matrix} {
}

void PlayerThread::run() {
    uint32_t elapsed = 0;
    while (!matrix.timeline.empty()) {
        while (!matrix.timeline.empty() && matrix.timeline.top().first == elapsed) {
            std::cout << "Mark hit: " << elapsed << ' ';
            emit markHit(matrix.timeline.top().second);
            matrix.timeline.pop();
        }

        if (matrix.timeline.empty()) break; // Proveravamo drugi put da li je prazan da ne bismo radili sleep ako nije potrebno.

        QThread::msleep(1);
        elapsed++;
    }

    emit playFinished();
}

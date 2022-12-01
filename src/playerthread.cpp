#include "playerthread.h"

#include <iostream>
#include <QDebug>

PlayerThread::PlayerThread(const Matrix& matrix, QObject *parent) : QThread(parent), matrix{matrix} {
}

void PlayerThread::run() {
    uint32_t elapsed = 0;
    QElapsedTimer timer;

    timer.start();
    while (!matrix.timeline.empty()) {
        while (!matrix.timeline.empty() && matrix.timeline.top().first <= elapsed) {
            qDebug() << matrix.timeline.top().first << " <= " << elapsed;
            std::cout << "Mark hit: " << elapsed << ' ';
            emit markHit(matrix.timeline.top().second);
            matrix.timeline.pop();
        }

        if (matrix.timeline.empty()) break; // Proveravamo drugi put da li je prazan da ne bismo radili sleep ako nije potrebno.

        elapsed = timer.elapsed();
    }

    emit playFinished();
}

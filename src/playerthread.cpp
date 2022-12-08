#include "playerthread.h"

#include <iostream>
#include <QDebug>

PlayerThread::PlayerThread(QObject *parent) : QThread(parent), sem_waitplay(1) {
}

void PlayerThread::run() {

    for (;;)
    {
        sem_waitplay.acquire();

        uint32_t elapsed = 0;
        QElapsedTimer timer;

        timer.restart();
        timer.start();
        elapsed = 0;
        while (!matrix.timeline.empty()) {
            while (!matrix.timeline.empty() && matrix.timeline.top().first.first <= elapsed) {
                qDebug() << matrix.timeline.top().first << " <= " << elapsed << ", size=" << matrix.timeline.size();
                emit markHit(matrix.timeline.top());
                matrix.timeline.pop();
            }

            if (matrix.timeline.empty()) break; // Proveravamo drugi put da li je prazan da ne bismo radili sleep ako nije potrebno.
            if (stop) { elapsed = 0; break; }                    // Ako je pozvana NewMatrix().

            elapsed = timer.elapsed();
        }

        if (stop)
        {
            stop = false;
        }
        else
        {
            qDebug() << "emit playFinished();";
            emit playFinished();
        }
    }
}

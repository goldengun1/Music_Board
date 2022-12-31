#include "playerthread.h"

PlayerThread::PlayerThread(QMutex *mutex, QObject *parent) : QThread(parent), pause(false), mutex(mutex), pausetime_accumulated(0) {
}

void PlayerThread::run() {
    uint32_t elapsed = 0;
    QElapsedTimer timer;

    timer.start();
    while (!matrix.timeline.empty())
    {
        elapsed = timer.elapsed() - pausetime_accumulated;
        if(elapsed % 100 == 0)
        {
            emit valueChanged(elapsed);
        }

        QMutexLocker lock(mutex);
        while (!matrix.timeline.empty() && matrix.timeline.top().first.first <= elapsed)
        {
            emit markHit(matrix.timeline.top());
            matrix.timeline.pop();
        }
    }

    qDebug() << "emit playFinished();";
    emit playFinished();
    emit valueChanged(0);
}

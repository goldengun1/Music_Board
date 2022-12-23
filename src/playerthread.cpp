#include "playerthread.h"

PlayerThread::PlayerThread(QMutex *mutex, QObject *parent) : QThread(parent), mutex(mutex) {
    pausetime_accumulated = 0;
    pause = false;
}

void PlayerThread::run() {
    uint32_t elapsed = 0;
    QElapsedTimer timer;

    timer.restart();
    timer.start();
    elapsed = 0;
    while (!matrix.timeline.empty())
    {
        elapsed = timer.elapsed() - pausetime_accumulated;
        if(elapsed % 100 == 0)
        {
            emit valueChanged(elapsed);
        }
        QMutexLocker lock(mutex);
        while (!matrix.timeline.empty() && matrix.timeline.top().first.first <= elapsed) {
//            qDebug() << matrix.timeline.top().first << " <= " << elapsed << ", size=" << matrix.timeline.size();
            emit markHit(matrix.timeline.top());
            matrix.timeline.pop();
        }
    }

    qDebug() << "emit playFinished();";
    emit playFinished();
    emit valueChanged(0);
}

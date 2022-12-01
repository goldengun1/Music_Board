#pragma once

#include <QThread>
#include <QSemaphore>

#include "matrix.h"

class PlayerThread: public QThread {
    Q_OBJECT
public:
    QSemaphore sem_waitplay;
    bool stop;

    explicit PlayerThread(QObject *parent = nullptr);

    void Stop(void) { stop = true; }
    void NewMatrix(const Matrix& matrix) { this->matrix = matrix; sem_waitplay.release(); }

protected:
    void run() override;

private:
    Matrix matrix;

signals:
    void playFinished();
    void markHit(sid sound);
};

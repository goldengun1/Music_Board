#pragma once

#include <QThread>

#include "matrix.h"

class PlayerThread: public QThread {
    Q_OBJECT
public:
    explicit PlayerThread(const Matrix& matrix, QObject *parent = nullptr);

protected:
    void run() override;

private:
    Matrix matrix;

signals:
    void playFinished();
    void markHit(sid sound);
};

#pragma once

#include <QThread>

class PlayerThread: public QThread {
    Q_OBJECT
public:
    explicit PlayerThread(QObject *parent = nullptr);

protected:
    void run() override;
};

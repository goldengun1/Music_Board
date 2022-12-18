#pragma once

#include <QObject>
#include <QMutex>

#include "soundbank.h"
#include "soundplayer.h"
#include "matrix.h"
#include "playerthread.h"

class MatrixPlayer: public QObject {
    Q_OBJECT

public:
    explicit MatrixPlayer(std::shared_ptr<SoundBank> bank, std::shared_ptr<SoundPlayer> player, QObject *parent = nullptr);
    ~MatrixPlayer();
    void PlayMatrix(const Matrix &);
    void Stop(void);
    void Pause(void);
    void DeleteMatrix(void);
    bool loopPlaying = false;

private:
    std::shared_ptr<SoundBank> bank;
    std::shared_ptr<SoundPlayer> player;
    PlayerThread *playerthread;
    QMutex mutex;

    void DeleteThread(void);

private slots:
    void onPlayFinished();
    void markHit(mark_t mark);
    void onValueChanged(int value);

signals:
    void matrixEnd();
    void valueChanged(int value);
};

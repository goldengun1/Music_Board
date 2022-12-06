#pragma once

#include <QObject>

#include "soundbank.h"
#include "soundplayer.h"
#include "matrix.h"
#include "playerthread.h"

class MatrixPlayer: public QObject {
    Q_OBJECT

public:
    explicit MatrixPlayer(std::shared_ptr<SoundBank> &bank, QObject *parent = nullptr);
    ~MatrixPlayer();
    void PlayMatrix(const Matrix &);
    void DeleteMatrix(void);

private:
    std::shared_ptr<SoundBank> bank;
    std::unique_ptr<SoundPlayer> player;
    PlayerThread *playerthread;

private slots:
    void onPlayFinished();
    void playSound(sid sound);
};

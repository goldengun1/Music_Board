#include "matrixplayer.h"

#include <iostream>

MatrixPlayer::MatrixPlayer(std::shared_ptr<SoundBank> &bank, QObject *parent)
    : QObject(parent)
    , bank{bank} {
    player = std::make_unique<SoundPlayer>(bank);

    playerthread = new PlayerThread(this);
    connect(playerthread, &QThread::finished, playerthread, &QThread::deleteLater);
    connect(playerthread, &PlayerThread::playFinished, this, &MatrixPlayer::onPlayFinished);
    connect(playerthread, &PlayerThread::markHit, this, &MatrixPlayer::playSound);
    playerthread->start();
}

void MatrixPlayer::PlayMatrix(const Matrix &matrix) {
    playerthread->NewMatrix(matrix);
}

void MatrixPlayer::onPlayFinished() {
    qDebug("Play finished (main thread)");
}

void MatrixPlayer::playSound(sid sound) {
    if (!player->Play(sound)) {
        // @TODO: handle error
        qDebug("Matrix player play fail");
    }
}

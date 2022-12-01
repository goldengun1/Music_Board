#include "matrixplayer.h"
#include "playerthread.h"

#include <iostream>

MatrixPlayer::MatrixPlayer(std::shared_ptr<SoundBank> &bank, QObject *parent)
    : QObject(parent)
    , bank{bank} {
    player = std::make_unique<SoundPlayer>(bank);
}

void MatrixPlayer::PlayMatrix(const Matrix &matrix) {
    auto playerThread = new PlayerThread(matrix, this);
    connect(playerThread, &QThread::finished, playerThread, &QThread::deleteLater);
    connect(playerThread, &PlayerThread::playFinished, this, &MatrixPlayer::onPlayFinished);
    connect(playerThread, &PlayerThread::markHit, this, &MatrixPlayer::playSound);

    playerThread->start();
}

void MatrixPlayer::onPlayFinished() {
    std::cout << "Play Finished" << '\n';
}

void MatrixPlayer::playSound(sid sound) {
    if (!player->Play(sound)) {
        // @TODO: handle error
        qDebug("Matrix player play fail");
    }
}

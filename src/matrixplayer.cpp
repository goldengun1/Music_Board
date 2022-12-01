#include "matrixplayer.h"
#include "playerthread.h"

MatrixPlayer::MatrixPlayer(QObject *parent) : QObject(parent) {

}

void MatrixPlayer::PlayMatrix() {
    auto playerThread = new PlayerThread(this);
    connect(playerThread, &QThread::finished, playerThread, &QThread::deleteLater);

    playerThread->start();
}

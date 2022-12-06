#include "matrixplayer.h"

#include <iostream>

MatrixPlayer::MatrixPlayer(std::shared_ptr<SoundBank> &bank, QObject *parent)
    : QObject(parent)
    , bank(bank),
    player(std::make_unique<SoundPlayer>(bank))
{
    playerthread = nullptr;
}
MatrixPlayer::~MatrixPlayer()
{
    // @TODO: ispitati da li je ovo najbolji nacin da se thread gasi kada se gasi i sama aplikacija
    playerthread->terminate();
    playerthread->wait();
}
void MatrixPlayer::PlayMatrix(const Matrix &matrix) {
    if (playerthread)
    {
        playerthread->terminate();
        playerthread->wait();
    }

    if (!playerthread)
    {
        playerthread = new PlayerThread(this);
        connect(playerthread, &PlayerThread::playFinished, this, &MatrixPlayer::onPlayFinished);
        connect(playerthread, &PlayerThread::markHit, this, &MatrixPlayer::playSound);
    }

    if (playerthread)
    {
        playerthread->NewMatrix(matrix);
        playerthread->start();
    }
}

void MatrixPlayer::DeleteMatrix(void)
{
    playerthread->terminate();
    playerthread->wait();
    playerthread = nullptr;
}

void MatrixPlayer::onPlayFinished() {
    qDebug("Play finished (main thread)");
}

void MatrixPlayer::playSound(sid sound) {
    if (playerthread && !player->Play(sound)) {
        // @TODO: handle error
        qDebug("Matrix player play fail");
    }
}

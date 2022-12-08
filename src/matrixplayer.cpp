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
    DeleteMatrix();
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
        connect(playerthread, &PlayerThread::markHit, this, &MatrixPlayer::markHit);
    }

    if (playerthread)
    {
        playerthread->NewMatrix(matrix);
        playerthread->start();
    }
}

void MatrixPlayer::DeleteMatrix(void)
{
    if (playerthread)
    {
        // @TODO: ispitati da li je ovo najbolji nacin da se thread gasi kada se gasi i sama aplikacija
        playerthread->terminate();
        playerthread->wait();
        playerthread = nullptr;
    }
}

void MatrixPlayer::onPlayFinished() {
    qDebug("Play finished (main thread)");
}

void MatrixPlayer::markHit(mark_t mark)
{
    //
    // No need to do anything if stopping fails,
    // as this can only happen if the sound already finished playing.
    //
    // If this is not a valid sound, MARK_PUSH will too do nothing.
    //
    switch (mark.first.second)
    {
    default:
    case MARK_PUSH:
        if (playerthread && !player->Play(mark.second))
        {
            // @TODO: handle error
            qDebug("Matrix player: invalid sound id?");
        }
        break;
    case MARK_RELEASE:
        if (playerthread)
        {
            player->Stop(mark.second);
        }
        break;
    }

}

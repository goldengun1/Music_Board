#include "matrixplayer.h"

MatrixPlayer::MatrixPlayer(std::shared_ptr<Recorder> recorder, std::shared_ptr<SoundPlayer> player, QObject *parent)
    : QObject(parent)
    , player(player)
    , recorder(recorder)
{
    playerthread = nullptr;
}

MatrixPlayer::~MatrixPlayer()
{
    DeleteThread();
}

void MatrixPlayer::PlayMatrix() {

    if(recorder->firstRecordingDuration != 0){
        if (playerthread){
            DeleteThread();
        }
        playerthread = new PlayerThread(&mutex, this);
        connect(playerthread, &PlayerThread::playFinished, this, &MatrixPlayer::onPlayFinished);
        connect(playerthread, &PlayerThread::markHit, this, &MatrixPlayer::markHit);
        connect(playerthread, &PlayerThread::valueChanged, this, &MatrixPlayer::onValueChanged);
        playerthread->NewMatrix(recorder->getMatrix());
        playerthread->start();
    }
}

void MatrixPlayer::DeleteThread(void)
{
    if (playerthread)
    {
        // @TODO: ispitati da li je ovo najbolji nacin da se thread gasi kada se gasi i sama aplikacija
        if (!playerthread->Paused())
        {
            mutex.lock();
        }
        playerthread->terminate();
        playerthread->wait();
        playerthread = nullptr;
        mutex.unlock();
    }
}

void MatrixPlayer::Stop(void)
{
    DeleteThread();
}

void MatrixPlayer::Pause(void)
{
    if (playerthread)
    {
        if (playerthread->Paused())
        {
            mutex.unlock();
            playerthread->Resume();
        }
        else
        {
            mutex.lock();
            playerthread->Pause();
        }
    }
}

void MatrixPlayer::onPlayFinished() {
    qDebug("Play finished (main thread)");
    DeleteThread();
    if (loopPlaying && recorder->firstRecordingDuration != 0){
        PlayMatrix();
    }
    emit matrixEnd();
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
    case MARK_REC_STOP:
        break;
    }

}

void MatrixPlayer::onValueChanged(int value)
{
    emit valueChanged(value);
}

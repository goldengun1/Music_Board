#include <QDebug>
#include "sound.h"

Sound::Sound(const QUrl &source, QObject *parent)
    : QObject(parent)
    , source(source)
    , player()
{
    connect(&player, &QMediaPlayer::mediaStatusChanged, this, &Sound::printMediaStatus);
    connect(&player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &Sound::printMediaError);
    player.setMedia(source);
}

Sound::~Sound(void)
{
    Stop();
    qDebug() << "Remove sound" << source ;
}

bool
Sound::Play(int masterVolume)
{
    player.setVolume(floor(effectVolume * masterVolume));
    if (IsPlaying()) player.stop();
    player.play();
    return true;
}

bool
Sound::Stop(void)
{
    if (IsPlaying())
    {
        player.stop();
        return true;
    }

    return false;
}

void Sound::setVolume(int volume)
{
    effectVolume = volume/100.0;
}

int Sound::getVolume() const
{
    return floor(effectVolume * 100);
}

quint64 Sound::Duration() const {
    return player.duration();
}

void Sound::printMediaStatus(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::MediaStatus::LoadedMedia)
        qDebug() << "Sound: " << source << ", status: " << status;
}

void Sound::printMediaError(QMediaPlayer::Error error) {
    qDebug() << "Sound: " << source << ", error: " << error;
}

bool Sound::IsPlaying() const {
    return player.state() == QMediaPlayer::PlayingState;
}


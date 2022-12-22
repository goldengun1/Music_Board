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
    player.play();
    return true;
}

bool
Sound::Stop(void)
{
    if (player.state() == QMediaPlayer::PlayingState)
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

void Sound::printMediaStatus(QMediaPlayer::MediaStatus status) {
    qDebug() << "Sound: " << source << ", status: " << status;
}

void Sound::printMediaError(QMediaPlayer::Error error) {
    qDebug() << "Sound: " << source << ", error: " << error;
}


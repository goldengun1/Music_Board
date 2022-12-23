#include "sound.h"

Sound::Sound(const QUrl &source)
    :source(source)
{
    qDebug() << "Create sound" << source;
    effect.setSource(source);
}

Sound::~Sound(void)
{
    Stop();
    qDebug() << "Remove sound" << source ;
}

bool
Sound::Play(int masterVolume)
{
    effect.setVolume(effectVolume*(masterVolume/100.0));
    effect.play();
    return true;
}

bool
Sound::Stop(void)
{
    if (effect.isPlaying())
    {
        effect.stop();
        return true;
    }

    return false;
}

void Sound::setVolume(int volume)
{
    effectVolume = volume/100.0;
}

int Sound::getVolume()
{
    return effectVolume*100;
}



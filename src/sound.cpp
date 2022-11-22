#include <QDebug>
#include "sound.h"

Sound::Sound(const QUrl &source)
    :source(source),
      playing(false)
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
Sound::Play(void)
{
    bool wasplaying = playing;

    if (!playing)
    {
        playing = true;
        effect.play();
    }

    return !wasplaying;
}

bool
Sound::Stop(void)
{
    bool wasstopped = !playing;

    if (!wasstopped)
    {
        playing = false;
        effect.stop();
    }

    return wasstopped;
}

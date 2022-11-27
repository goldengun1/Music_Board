#include <QDebug>
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
Sound::Play(void)
{
    if (!effect.isPlaying())
    {
        effect.play();
        return true;
    }

    return false;
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

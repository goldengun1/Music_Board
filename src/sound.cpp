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
    effect.setVolume(0);
    effect.play();
    fadeVolume(0, _volume, fadeTime);
    return true;
}

bool
Sound::Stop(void)
{
    fadeVolume(_volume, 0, fadeTime);
    //effect.stop();
    return true;
}

void Sound::setVolume(int volume)
{
    effect.setVolume(volume/100.0);
    _volume = volume;
}

int Sound::volume()
{
    return effect.volume()*100;
}

void Sound::fadeVolume(int startValue, int endValue, std::chrono::milliseconds time)
{
    using namespace std::chrono;
    long long nanoTime = nanoseconds{time}.count();
    auto startTime = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
    auto endTime = startTime + nanoseconds{time}.count();
    auto oldTime = startTime;
    auto newTime = startTime;
    qreal dv;
    long long dt;
    if(startValue > endValue){
        dv = (startValue - endValue)/100.0;
        while (newTime < endTime){
            dt = newTime - oldTime;
            effect.setVolume(effect.volume()-(dv*dt/nanoTime));
            oldTime = newTime;
            newTime = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
            //qDebug() << (duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count() - startTime)/1000000;
        }
        effect.setVolume(0);
    } else {
        dv = (endValue - startValue)/100.0;
        while (newTime < endTime){
            dt = newTime - oldTime;
            effect.setVolume(effect.volume()+(dv*dt/nanoTime));
            oldTime = newTime;
            newTime = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
            //qDebug() << effect.volume();
        }
        effect.setVolume(_volume/100.0);
    }

}



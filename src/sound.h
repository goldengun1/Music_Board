#pragma once

#include <QSoundEffect>
#include <QUrl>

class Sound
{
    QSoundEffect effect;
    const QUrl source;

public:
    Sound(const QUrl &source);
    ~Sound(void);

    bool Play(void);
    bool Stop(void);

    QUrl Source(void) const { return source; }
};

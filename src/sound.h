#pragma once

#include <QSoundEffect>
#include <QUrl>

///
/// Play sound files.
/// Meant to be held by a SoundBank object.
/// Source can be a local file, example - QUrl::fromLocalFile("path...").
///
class Sound
{
    QSoundEffect effect;
    const QUrl source;

public:
    Sound(const QUrl &source);
    ~Sound(void);

    bool Play(void); // Play sound, return true if it was previously stopped.
    bool Stop(void); // Stop sound, return true if it was previously playing.

    QUrl Source(void) const { return source; }
};

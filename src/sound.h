#pragma once

#include <QSoundEffect>
#include <QUrl>
#include <thread>
#include <chrono>

///
/// Play sound files.
/// Meant to be held by a SoundBank object.
/// Source can be a local file, example - QUrl::fromLocalFile("path...").
///
class Sound
{
    QSoundEffect effect;
    const QUrl source;
    int _volume = 100;
    const std::chrono::milliseconds fadeTime = std::chrono::milliseconds{500};

public:
    Sound(const QUrl &source);
    ~Sound(void);

    bool Play(void); // Play sound, return true if it was previously stopped.
    bool Stop(void); // Stop sound, return true if it was previously playing.

    QUrl Source(void) const { return source; }

    bool oneShot {true};

    void setVolume(int volume);
    int volume();

    void fadeVolume(int start_value, int end_value, std::chrono::milliseconds time);
};

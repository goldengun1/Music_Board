#pragma once

#include <map>
#include <memory>
#include <optional>
#include <QSoundEffect>

// Sound identifier type.
typedef uint32_t sid;

class Sound
{
    QSoundEffect effect;
    const QUrl source;
    bool playing;

public:
    Sound(const QUrl &source);
    ~Sound(void);

    bool Play(void);
    bool Stop(void);

    QUrl Source(void) const { return source; }
};

class SoundBank
{
    std::map<sid, std::shared_ptr<Sound>> sound;

public:
    SoundBank();
    ~SoundBank(void);

    sid Assign(const sid index, std::shared_ptr<Sound> sound);
    sid Unassign(const sid index) { return Assign(index, nullptr); }
    std::optional<std::shared_ptr<Sound>> Assigned(const sid index);
};

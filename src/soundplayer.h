#pragma once

#include <vector>
#include <memory>
#include <optional>
#include "soundbank.h"

///
/// Using the given SoundBank, play sounds.
///
class SoundPlayer: public QObject
{
    std::shared_ptr<SoundBank> bank;

public:
    SoundPlayer(std::shared_ptr<SoundBank> bank);
    ~SoundPlayer(void);

    int masterVolume {100};

    [[nodiscard("HANDLE INVALID INDEX")]]
    bool Play(const sid index);
    bool Stop(const sid index);

public slots:
    void handleMasterVolumeChange(const int newVolume);
};

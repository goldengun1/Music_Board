#pragma once

#include <vector>
#include <memory>
#include <optional>
#include "soundbank.h"

///
/// Using the given SoundBank, play sounds.
///
class SoundPlayer
{
    std::shared_ptr<SoundBank> bank;

public:
    SoundPlayer(std::shared_ptr<SoundBank> bank);
    ~SoundPlayer(void);

    [[nodiscard("HANDLE INVALID INDEX")]]
    bool Play(const sid index);
};

#pragma once

#include <map>
#include <memory>
#include <optional>
#include "sound.h"

// Sound identifier type.
typedef uint32_t sid;

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
